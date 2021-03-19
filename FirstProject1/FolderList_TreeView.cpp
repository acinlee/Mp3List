#pragma once
#include "FolderList_TreeView.h"
#include <CommCtrl.h>
#include <sstream>
#include "global.h"
#pragma comment(lib, "comctl32.lib")

TreeView_FolderList::TreeView_FolderList():m_ParentWnd(NULL), m_hTreeFolerList(NULL),
m_hInstance(NULL), m_TI({0}), m_HTREE(NULL), m_x(0), m_y(0), m_width(0), m_height(0)
{
}

HWND TreeView_FolderList::Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height)
{
	m_ParentWnd = hWnd;
	m_hInstance = hInstance;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	return (m_hTreeFolerList = CreateWindow(WC_TREEVIEW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT, x, y, width, height, hWnd, NULL, m_hInstance, NULL));
}

void TreeView_FolderList::InsertRootFolder(WCHAR* path)
{
	TreeView_DeleteAllItems(m_hTreeFolerList);
	m_TI.hParent = TVI_ROOT;
	m_TI.hInsertAfter = TVI_LAST;
	m_TI.item.mask = TVIF_TEXT;
	m_TI.item.pszText = path;
	m_HTREE = TreeView_InsertItem(m_hTreeFolerList, &m_TI);
	
	//todo : wstringstream
	std::wstringstream nextpath;
	nextpath << path;
	nextpath << "\\*.*";
	nextpath >> path;

	InsertFolderList(path, m_HTREE);
}

void TreeView_FolderList::InsertFolderList(WCHAR* path, HTREEITEM hParent)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	TCHAR drive[_MAX_DRIVE]; //드라이브명
	TCHAR dir[_MAX_DIR]; //디렉토리 경로
	TCHAR fname[_MAX_FNAME]; // 파일명
	TCHAR ext[_MAX_EXT]; //확장자 명
	TCHAR newpath[MAX_PATH];
	std::wstringstream nextpath;

	hSrch = FindFirstFile(path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE)
	{
		return;
	}

	_wsplitpath_s(path, drive, dir, fname, ext);

	while (bResult)
	{
		//디렉토리인지 검사
		if (wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, Global::toLPWSTR(const_cast<char*>("."))) && lstrcmp(wfd.cFileName, Global::toLPWSTR(const_cast<char*>(".."))))
			{
				nextpath << path;
				nextpath << "\\*.*";
				nextpath >> newpath;
				InsertFolderList(newpath, m_HTREE);
			}
			else
			{
				nextpath << dir;
				nextpath >> newpath;
				m_TI.hParent = m_HTREE;
				m_TI.hInsertAfter = TVI_LAST;
				m_TI.item.mask = TVIF_TEXT;
				m_TI.item.pszText = newpath;
				m_HTREE = TreeView_InsertItem(m_hTreeFolerList, &m_TI);
			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}
