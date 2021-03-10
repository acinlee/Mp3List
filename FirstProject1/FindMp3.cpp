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

//트리뷰
HWND hTreeDirectory;
//리스트뷰
HWND hListViewDirectory;

//폴더 등록 버튼
HWND hFolderUploadBtn;

//선택한 폴더 경로
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
	TCHAR full_path[MAX_PATH]; //전체 경로
	TCHAR drive[_MAX_DRIVE]; //드라이브명
	TCHAR dir[_MAX_DIR]; //디렉토리 경로
	TCHAR fname[_MAX_FNAME]; // 파일명
	TCHAR ext[_MAX_EXT]; //확장자 명
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
		//디렉토리인지 검사
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, ".."))
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				FindFileRecursive(newpath);
			}
			else
			{
				//여기서 파일 split해서 sendmessage to listview
				wsprintf(fname, "%s%s%s", drive, dir, wfd.cFileName);

				SendMessage(hListViewDirectory, LVM_SETITEM, 0, (LPARAM)fname);

			}
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}*/

//디렉토리 트리뷰
/*void DirTreeView_Insert(TCHAR* path, HTREEITEM Parent_TREE)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	//TCHAR full_path[MAX_PATH]; //전체 경로
	TCHAR drive[_MAX_DRIVE]; //드라이브명
	TCHAR dir[_MAX_DIR]; //디렉토리 경로
	TCHAR fname[_MAX_FNAME]; // 파일명
	TCHAR ext[_MAX_EXT]; //확장자 명
	TCHAR newpath[MAX_PATH];

	//트리뷰
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
		//디렉토리인지 검사
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

	//리스트뷰
	LVCOLUMN COL;
	LVITEM LI;

	//트리뷰
	TVINSERTSTRUCT TI;
	HTREEITEM HTREE;

	//사용자 선택 폴더
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
		hFolderUploadBtn = CreateWindow(TEXT("button"), "폴더등록", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 440, 20, 100, 25, hWnd, (HMENU)ID_hFolderUpload_Btn, g_hInst, NULL);
		hComboBoxPath = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 400, 25, hWnd, (HMENU)ID_hFile_Route_Combobox, g_hInst, NULL);

		//트리뷰

		// 리스트뷰
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		//static_cast<>;
		//reinterpret_cast<>;
		//const_cast<>;
		//dynamic_cast<>;
		//float - > dpuble;
		//long -> int
		COL.pszText = const_cast<char*>("곡명");
		COL.iSubItem = 0;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

		COL.cx = 20;
		COL.pszText = (LPSTR)"#";
		COL.iSubItem = 1;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

		COL.cx = 150;
		COL.pszText = (LPSTR)"제목";
		COL.iSubItem = 2;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

		COL.cx = 150;
		COL.pszText = (LPSTR)"참여음악가";
		COL.iSubItem = 3;
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

		COL.cx = 150;
		COL.pszText = (LPSTR)"앨범";
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
				//사용자가 선택한 폴더 root로 만들기

				/*TI.hParent = TVI_ROOT;
				TI.hInsertAfter = TVI_LAST;
				TI.item.mask = TVIF_TEXT;
				TI.item.pszText = RootDir;
				HTREE = TreeView_InsertItem(hTreeDirectory, &TI);*/

				//root 하위 디렉토리 트리뷰
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


