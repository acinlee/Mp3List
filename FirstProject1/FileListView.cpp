#pragma warning(disable:4996)
#include "FileListView.h"
#include "global.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <cstdio>
#include <vcruntime_string.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

FileListView::FileListView() :m_hParent(NULL), m_FileListView(NULL), m_hInstance(NULL), m_x(0), m_y(0), m_width(0), m_height(0),
m_COL({ 0, }), m_LI({ 0, })
{
}

HWND FileListView::Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	m_hParent = hWnd;
	m_hInstance = hInstance;
	m_FileListView = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, x, y, width, height, m_hParent, NULL, m_hInstance, NULL);

	m_COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	m_COL.fmt = LVCFMT_LEFT;
	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR(const_cast<char*>("곡명"));
	m_COL.iSubItem = 0;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 0, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR(const_cast<char*>("Artist"));
	m_COL.iSubItem = 1;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 1, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR(const_cast<char*>("제작년도"));
	m_COL.iSubItem = 2;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 2, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = Global::toLPWSTR(const_cast<char*>("앨범"));
	m_COL.iSubItem = 3;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 3, (LPARAM)&m_COL);

	return m_FileListView;
}

void FileListView::FileListInsert(WCHAR* path)
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
	std::wstring path1;
	SongInfo song;
	hSrch = FindFirstFile(path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE)
	{
		return;
	}

	//_splitpath_s(path, drive, dir, fname, ext);

	while (bResult)
	{
		//디렉토리인지 검사
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			if (lstrcmp(wfd.cFileName, Global::toLPWSTR(const_cast<char*>("."))) && lstrcmp(wfd.cFileName, Global::toLPWSTR(const_cast<char*>(".."))))
			{
				nextpath << path;
				nextpath << "\\*.*";
				nextpath >> newpath;
				FileListInsert(newpath);
			}
		}
		else
		{
			//여기서 파일 split해서 sendmessage to listview
			nextpath << drive;
			nextpath << dir;
			nextpath << wfd.cFileName;
			nextpath >> path1;
			//Mp3Info(path1, &song);

			m_LI.mask = LVIF_TEXT;
			m_LI.iSubItem = 0;
			m_LI.iItem = 0;
			m_LI.pszText = Global::toLPWSTR(song.title);
			SendMessage(m_FileListView, LVM_INSERTITEM, 0, (LPARAM)&m_LI);

			m_LI.iSubItem = 1;
			m_LI.pszText = Global::toLPWSTR(song.artist);
			SendMessage(m_FileListView, LVM_INSERTITEM, 0, (LPARAM)&m_LI);

			m_LI.iSubItem = 2;
			m_LI.pszText = Global::toLPWSTR(song.year);
			SendMessage(m_FileListView, LVM_INSERTITEM, 0, (LPARAM)&m_LI);

			m_LI.iSubItem = 3;
			m_LI.pszText = Global::toLPWSTR(song.album);
			SendMessage(m_FileListView, LVM_INSERTITEM, 0, (LPARAM)&m_LI);
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}

//BOOL FileListView::Mp3Info(WCHAR* filename, SongInfo* song)
//{
//	
//	FILE* fh;
//	if ((fh = fopen(filename, "rb")) == NULL) 
//	{
//		return FALSE;
//	}
//	else 
//	{
//		char raw[128];
//
//		fseek(fh, -128L, SEEK_END);
//		fread(raw, 1, 128, fh);
//		fclose(fh);
//
//		if (raw[0] != 'T' || raw[1] != 'A' || raw[2] != 'G') 
//		{
//			return FALSE;
//		}
//		else 
//		{
//			char* b = raw + 3;
//
//			song->title[30] = 0;
//			memcpy(song->title, b, 30);
//			b += 30;
//
//			song->artist[30] = 0;
//			memcpy(song->artist, b, 30);
//			b += 30;
//
//			song->album[30] = 0;
//			memcpy(song->album, b, 30);
//			b += 30;
//
//			song->year[4] = 0;
//			memcpy(song->year, b, 4);
//			b += 4;
//		}
//	}
//	return TRUE;
//}
/*std::ifstream file(filename, std::ios::binary);
	if (file.fail())
	{
		return FALSE;
	}
	else
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);
		char* buffer = new char[length];
		char* jumpmemory = buffer + 3;

		memcpy(song->title, jumpmemory, 30);
		jumpmemory += 30;

		memcpy(song->artist, jumpmemory, 30);
		jumpmemory += 30;

		memcpy(song->album, jumpmemory, 30);
		jumpmemory += 30;

		memcpy(song->year, jumpmemory, 4);
		jumpmemory += 30;
	}*/