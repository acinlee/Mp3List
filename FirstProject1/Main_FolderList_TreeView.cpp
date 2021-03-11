#include "FolderList_TreeView.h"

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
	return (m_hTreeFolerList=CreateWindow(WC_TREEVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT, 10, 100, 400, 200, hWnd, NULL, hInstance, NULL));
}

void TreeView_FolderList::InsertFolderList()
{
	m_TI.hParent = TVI_ROOT;
	m_TI.hInsertAfter = TVI_LAST;
	m_TI.item.mask = TVIF_TEXT;
	m_TI.item.pszText = const_cast<char*>("hello");
	m_HTREE = TreeView_InsertItem(m_hTreeFolerList, &m_TI);
}
