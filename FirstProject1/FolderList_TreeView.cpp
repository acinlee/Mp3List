#pragma once
#include "FolderList_TreeView.h"
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

TreeView_FolderList::TreeView_FolderList()
{
	m_ParentWnd = NULL;
	m_hTreeFolerList = NULL;
	m_hInstance = NULL;
	m_TI = {0,};
	m_HTREE = {0,};
}

HWND TreeView_FolderList::Create(HWND hWnd, HINSTANCE hInstance)
{
	m_ParentWnd = hWnd;
	m_hInstance = hInstance;
	return (m_hTreeFolerList=CreateWindow(WC_TREEVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT, 10, 100, 400, 200, hWnd, NULL, m_hInstance, NULL));
}

void TreeView_FolderList::InsertRootFolder(TCHAR* path)
{
	TreeView_DeleteAllItems(m_hTreeFolerList);
	m_TI.hParent = TVI_ROOT;
	m_TI.hInsertAfter = TVI_LAST;
	m_TI.item.mask = TVIF_TEXT;
	m_TI.item.pszText = path;
	m_HTREE = TreeView_InsertItem(m_hTreeFolerList, &m_TI);
	
	//todo : stringstream
	wsprintf(path, "%s\\*.*", path);

	InsertFolderList(path, m_HTREE);
}

void TreeView_FolderList::InsertFolderList(TCHAR* path, HTREEITEM Parent_TREE)
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
		if (wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, ".."))
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				InsertFolderList(newpath, Parent_TREE);
			}
			else
			{
				wsprintf(newpath, "%s", dir);
				m_TI.hParent = Parent_TREE;
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