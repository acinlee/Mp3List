#include "FileListView.h"
#include "global.h"
#include <fstream>
#include <istream>
#include <sstream>
//#include <cstdio>
//#include <vcruntime_string.h>
#include <CommCtrl.h>
#include <comdef.h> 
#pragma comment(lib, "comctl32.lib")

FileListView::FileListView() :m_hParent(NULL), m_FileListView(NULL), m_hInstance(NULL), m_x(0), m_y(0), m_width(0), m_height(0),
m_COL({ 0, }), m_LI({ 0, }), songs()
{
}

void FileListView::Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	m_hParent = hWnd;
	m_hInstance = hInstance;
	m_FileListView = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, x, y, width, height, m_hParent, NULL, m_hInstance, NULL);
	ListView_SetExtendedListViewStyle(m_FileListView, LVS_EX_FULLROWSELECT);

	m_COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	m_COL.fmt = LVCFMT_LEFT;
	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR("곡명");
	m_COL.iSubItem = 0;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 0, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR("Artist");
	m_COL.iSubItem = 1;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 1, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR("제작년도");
	m_COL.iSubItem = 2;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 2, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR("앨범");
	m_COL.iSubItem = 3;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 3, (LPARAM)&m_COL);
}

void FileListView::SongStructInsert(WCHAR* path)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	WCHAR drive[_MAX_DRIVE]; //드라이브명
	WCHAR dir[_MAX_DIR]; //디렉토리 경로
	WCHAR fname[_MAX_FNAME]; // 파일명
	WCHAR ext[_MAX_EXT]; //확장자 명
	WCHAR newpath[MAX_PATH];
	std::wstringstream nextpath;
	SongInfo song;
	hSrch = FindFirstFile(path, &wfd);

	if (hSrch == INVALID_HANDLE_VALUE)
	{
		return;
	}

	_wsplitpath_s(path, drive, dir, fname, ext);

	while (bResult)
	{
		//디렉토리인지 검사
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			if (lstrcmp(wfd.cFileName, Global::toLPWSTR(".")) && lstrcmp(wfd.cFileName, Global::toLPWSTR("..")))
			{
				nextpath << path;
				nextpath << "\\*.*";
				nextpath >> newpath;
				SongStructInsert(newpath);
			}
		}
		else
		{
			//21.03.24 오류 같은 파일이 반복되는 오류 - 특정 파일에서 발생하는 오류로 Mp3Info 함수를 수정해야됨(idv1->idv2)
			nextpath << drive;
			nextpath << dir;
			nextpath << wfd.cFileName;
			lstrcpy(newpath, nextpath.str().c_str());
			Mp3Info(newpath, &song);

			songs.push_back(song);
			nextpath.str(L"");
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}

//여기도 c가 아닌 c++처럼 수정
BOOL FileListView::Mp3Info(WCHAR* filename, SongInfo* song)
{
	FILE* fh;
	errno_t errno;
	errno = _wfopen_s(&fh, filename, L"rb");
	if (errno != 0)
	{
		return FALSE;
	}
	else
	{
		char raw[128];

		fseek(fh, -128L, SEEK_END);
		fread(raw, 1, 128, fh);
		fclose(fh);

		if (raw[0] != 'T' || raw[1] != 'A' || raw[2] != 'G')
		{
			return FALSE;
		}
		else
		{
			char* b = raw + 3;

			song->title[30] = 0;
			memcpy(song->title, b, 30);
			b += 30;

			song->artist[30] = 0;
			memcpy(song->artist, b, 30);
			b += 30;

			song->album[30] = 0;
			memcpy(song->album, b, 30);
			b += 30;

			song->year[4] = 0;
			memcpy(song->year, b, 4);
			b += 4;
		}
	}
	return TRUE;
}

HWND FileListView::getListView()
{
	return m_FileListView;
}

BOOL FileListView::FileListInsert()
{
	for (int i = 0; i < songs.size(); ++i)
	{
		int idx = ListView_GetItemCount(getListView());
		m_LI.mask = LVIF_TEXT;
		m_LI.iSubItem = 0;
		m_LI.iItem = idx;
		m_LI.pszText = Global::toLPWSTR(songs[i].title);
		ListView_InsertItem(getListView(), &m_LI);
		ListView_SetItemText(getListView(), idx, 1, Global::toLPWSTR(songs[i].artist));
		ListView_SetItemText(getListView(), idx, 2, Global::toLPWSTR(songs[i].year));
		ListView_SetItemText(getListView(), idx, 3, Global::toLPWSTR(songs[i].album));
	}
	return TRUE;
}

BOOL FileListView::SelectItem()
{
	int idx = ListView_GetNextItem(m_FileListView, -1, LVNI_ALL | LVNI_SELECTED);// 선택 항목
	if (idx == -1)
	{
		return FALSE;
	}
	else
	{
		/*char dialogtitle[31] = { 0 };
		char dialogartist[31] = { 0 };
		char dialogyear[31] = { 0 };
		char dialogalbum[31] = { 0 };
		ListView_GetItemText(getListView(), idx, 0, Global::toLPWSTR(dialogtitle), 31);
		ListView_GetItemText(getListView(), idx, 1, Global::toLPWSTR(dialogartist), 31);
		ListView_GetItemText(getListView(), idx, 2, Global::toLPWSTR(dialogyear), 31);
		ListView_GetItemText(getListView(), idx, 3, Global::toLPWSTR(dialogalbum), 31);
		*///다이얼로그 박스 create할때 리스트뷰의 텍스트 값 같이 보내서 초기화 해야됨
		m_mp3InfoWnd.Create(m_hParent, Global::get_hInstance());
		//m_mp3InfoWnd.setText(dialogtitle, dialogartist, dialogyear, dialogalbum);
	}
	return TRUE;
}