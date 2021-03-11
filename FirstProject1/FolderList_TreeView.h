#ifndef FolderList_TreeView
#define FolderList_TreeView
#include <windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

class TreeView_FolderList
{
public:
	HWND m_ParentWnd;
	HWND m_hTreeFolerList;
	HINSTANCE m_hInstance;

public:
	//Ʈ����
	TVINSERTSTRUCT m_TI;
	HTREEITEM m_HTREE;

	//����� ���� ����
	//TCHAR RootDir[MAX_PATH];

public:
	TreeView_FolderList();
	HWND Create(HWND hWnd, HINSTANCE hInstance);
	void InsertFolderList();
};
#endif // !FileList_TreeView
