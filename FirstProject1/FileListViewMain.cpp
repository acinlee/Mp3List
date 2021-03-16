#include "FileListView.h"
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

FileListView::FileListView():m_hParent(NULL), m_FileListView(NULL), m_hInstance(NULL), m_x(0), m_y(0), m_width(0), m_height(0),
m_COL({0,}), m_LI({0,}), m_filenum(0)
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
	m_COL.pszText = const_cast<char*>("���");
	m_COL.iSubItem = 0;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 0, (LPARAM)&m_COL);

	m_COL.cx = 20;
	m_COL.pszText = const_cast<char*>("#");
	m_COL.iSubItem = 1;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 1, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("����");
	m_COL.iSubItem = 2;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 2, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("�������ǰ�");
	m_COL.iSubItem = 3;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 3, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("�ٹ�");
	m_COL.iSubItem = 4;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 4, (LPARAM)&m_COL);

	return m_FileListView;
}

void FileListView::FileListInsert(TCHAR *path, int file_num)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	TCHAR drive[_MAX_DRIVE]; //����̺��
	TCHAR dir[_MAX_DIR]; //���丮 ���
	TCHAR fname[_MAX_FNAME]; // ���ϸ�
	TCHAR ext[_MAX_EXT]; //Ȯ���� ��
	TCHAR newpath[MAX_PATH];
	
	
	hSrch = FindFirstFile(path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE)
	{
		return;
	}
	_splitpath_s(path, drive, dir, fname, ext);

	while (bResult)
	{
		//���丮���� �˻�
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, ".."))
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				++file_num;
				FileListInsert(newpath, file_num);
			}
			else
			{
				//���⼭ ���� split�ؼ� sendmessage to listview
				LPSTR texts = NULL;
				wsprintf(fname, "%s%s%s", drive, dir, wfd.cFileName);
				//TagLib::FileRef f(fname);
				/*TagLib::String artist = f.tag()->artist();
				wsprintf(texts, "%s", artist);
				
				m_LI.iSubItem = 0;
				m_LI.iItem = file_num;*/
				//m_LI.pszText = texts;
				/*if (id3Tag.Open(fname) == TRUE)
				{
					if (id3Tag.ContainsInfo(MetadataInfo::ID3::TITLE) == TRUE)
					{
						m_LI.iSubItem = 0;
						m_LI.iItem = file_num;
						m_LI.pszText = const_cast<char*>(UTF16ToUTF8(id3Tag.GetStringValue(MetadataInfo::ID3::TITLE).c_str()).c_str());
						long frameDataSize = id3Tag.GetBinarySize(MetadataInfo::ID3::COVER_IMAGE);
						char* buffer = (char*)malloc(frameDataSize);
						id3Tag.GetBinaryValue(MetadataInfo::ID3::COVER_IMAGE, buffer, frameDataSize);
						long imageDataSize = 0; 
						const char* imageData = id3Tag.GetBinaryImage(buffer, frameDataSize, imageDataSize);
					}
				}*/
				SendMessage(m_FileListView, LVM_INSERTITEM, 0, (LPARAM)&m_LI);

			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}