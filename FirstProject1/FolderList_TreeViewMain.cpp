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

void TreeView_FolderList::InsertFolderList(TCHAR* path, HTREEITEM Parent_TREE)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	//TCHAR full_path[MAX_PATH]; //��ü ���
	TCHAR drive[_MAX_DRIVE]; //����̺��
	TCHAR dir[_MAX_DIR]; //���丮 ���
	TCHAR fname[_MAX_FNAME]; // ���ϸ�
	TCHAR ext[_MAX_EXT]; //Ȯ���� ��
	TCHAR newpath[MAX_PATH];

	//Ʈ����
	TVINSERTSTRUCT TI;
	HTREEITEM HTREE;

	hSrch = FindFirstFile(path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE)
	{
		return;
	}
	_splitpath_s(path, drive, dir, fname, ext);

	TI.hParent = Parent_TREE;
	TI.hInsertAfter = TVI_LAST;
	TI.item.mask = TVIF_TEXT;
	TI.item.pszText = dir;
	HTREE = TreeView_InsertItem(m_hTreeFolerList, &TI);

	while (bResult)
	{
		//���丮���� �˻�
		if (wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, ".."))
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				InsertFolderList(newpath, HTREE);
			}
			else
			{
				wsprintf(newpath, "%s", dir);
				TI.hParent = HTREE;
				TI.hInsertAfter = TVI_LAST;
				TI.item.mask = TVIF_TEXT;
				TI.item.pszText = newpath;
				HTREE = TreeView_InsertItem(m_hTreeFolerList, &TI);
			}
		}
		bResult = FindNextFile(hSrch, &wfd);

	}
	FindClose(hSrch);
}
