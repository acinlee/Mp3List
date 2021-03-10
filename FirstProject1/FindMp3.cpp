#include "MainWindowHeader.h"
#include <windows.h>
#include <CommCtrl.h>
#include <SHLOBJ.H>
#pragma comment(lib, "comctl32.lib")

BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder);
int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Mp3List");

//Ʈ����
HWND hTreeDirectory;
//����Ʈ��
HWND hListViewDirectory;

//���� ��� ��ư
HWND hFolderUploadBtn;

//������ ���� ���
HWND hComboBoxPath;

enum
{
	ID_hListView_File = 100,
	ID_hTreeView_Folder = 200,
	ID_hFile_Route_Combobox = 300,
	ID_hFolderUpload_Btn = 401,

};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	//main_window.Create();
	MainWindow main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	main.Create();

	while (GetMessage(&main.m_Message, NULL, 0, 0))
	{
		TranslateMessage(&main.m_Message);
		DispatchMessage(&main.m_Message);
	}

	return (int)main.m_Message.wParam;
}

/*void FindFileRecursive(TCHAR* path)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	TCHAR full_path[MAX_PATH]; //��ü ���
	TCHAR drive[_MAX_DRIVE]; //����̺��
	TCHAR dir[_MAX_DIR]; //���丮 ���
	TCHAR fname[_MAX_FNAME]; // ���ϸ�
	TCHAR ext[_MAX_EXT]; //Ȯ���� ��
	TCHAR newpath[MAX_PATH];

	LVITEM LI;

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
				FindFileRecursive(newpath);
			}
			else
			{
				//���⼭ ���� split�ؼ� sendmessage to listview
				wsprintf(fname, "%s%s%s", drive, dir, wfd.cFileName);

				SendMessage(hListViewDirectory, LVM_SETITEM, 0, (LPARAM)fname);

			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}*/

//���丮 Ʈ����
/*void DirTreeView_Insert(TCHAR* path, HTREEITEM Parent_TREE)
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
	HTREE = TreeView_InsertItem(hTreeDirectory, &TI);
	
	while (bResult)
	{
		//���丮���� �˻�
		if (wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, ".."))
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				DirTreeView_Insert(newpath, HTREE);
			}
			else
			{
				wsprintf(newpath, "%s", dir);
				TI.hParent = HTREE;
				TI.hInsertAfter = TVI_LAST;
				TI.item.mask = TVIF_TEXT;
				TI.item.pszText = newpath;
				HTREE = TreeView_InsertItem(hTreeDirectory, &TI);
			}
		}
		bResult = FindNextFile(hSrch, &wfd);

	}
	FindClose(hSrch);
}*/

/*LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	//����Ʈ��
	LVCOLUMN COL;
	LVITEM LI;

	//Ʈ����
	TVINSERTSTRUCT TI;
	HTREEITEM HTREE;

	//����� ���� ����
	TCHAR RootDir[MAX_PATH];
	//TCHAR Path[MAX_PATH];

	//int i;

	switch (iMessage)
	{
	case WM_CREATE:
		//OnCreate();
		InitCommonControls();
		hListViewDirectory = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, 410, 100, 620, 200, hWnd, NULL, g_hInst, NULL);
		hTreeDirectory = CreateWindow(WC_TREEVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT, 10, 100, 400, 200, hWnd, NULL, g_hInst, NULL);
		hFolderUploadBtn = CreateWindow(TEXT("button"), "�������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 440, 20, 100, 25, hWnd, (HMENU)ID_hFolderUpload_Btn, g_hInst, NULL);
		hComboBoxPath = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 400, 25, hWnd, (HMENU)ID_hFile_Route_Combobox, g_hInst, NULL);

		//Ʈ����

		// ����Ʈ��
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		//static_cast<>;
		//reinterpret_cast<>;
		//const_cast<>;
		//dynamic_cast<>;
		//float - > dpuble;
		//long -> int
		COL.pszText = const_cast<char*>("���");
		COL.iSubItem = 0;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

		COL.cx = 20;
		COL.pszText = (LPSTR)"#";
		COL.iSubItem = 1;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

		COL.cx = 150;
		COL.pszText = (LPSTR)"����";
		COL.iSubItem = 2;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

		COL.cx = 150;
		COL.pszText = (LPSTR)"�������ǰ�";
		COL.iSubItem = 3;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

		COL.cx = 150;
		COL.pszText = (LPSTR)"�ٹ�";
		COL.iSubItem = 4;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_hFolderUpload_Btn:
			//GetWindowsDirectory(RootDir, MAX_PATH);
			if (BrowseFolder(hWnd, NULL, NULL, RootDir) == TRUE)
			{
				SetWindowText(hComboBoxPath, RootDir);
				//����ڰ� ������ ���� root�� �����

				/*TI.hParent = TVI_ROOT;
				TI.hInsertAfter = TVI_LAST;
				TI.item.mask = TVIF_TEXT;
				TI.item.pszText = RootDir;
				HTREE = TreeView_InsertItem(hTreeDirectory, &TI);*/

				//root ���� ���丮 Ʈ����
				/*DirTreeView_Insert(RootDir, (HTREEITEM)0);
			}
		}
		return FALSE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}*/

/*int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
	case BFFM_INITIALIZED:
		if (lpData != NULL) {
			SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi = { 0, };

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL) {
		return FALSE;
	}
	SHGetPathFromIDList(pidl, szFolder);

	if (SHGetMalloc(&pMalloc) != NOERROR) {
		return FALSE;
	}
	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
}*/


