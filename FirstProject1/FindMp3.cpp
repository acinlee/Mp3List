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
//HWND hTreeDirectory;
//리스트뷰
//HWND hListViewDirectory;

//폴더 등록 버튼
HWND hFolderUploadBtn;

enum
{
	ID_hListView_File = 100,
	ID_hTreeView_Folder = 200,
	ID_hFile_Route_Combobox = 300,
	ID_hFolderUpload_Btn = 401
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//넓이, 높이 변경 시 윈도우 다시 그림
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}
/*
void FindFileRecursive(TCHAR* path)
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
}

void DirTreeView(TCHAR* path)
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

	TVINSERTSTRUCT TI;

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
}
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	/*LVCOLUMN COL;
	LVITEM LI;*/
	TCHAR RootDir[MAX_PATH];
	TCHAR Path[MAX_PATH];
	//int i;
	switch (iMessage)
	{
	case WM_CREATE:
		//InitCommonControls();
		//hListViewDirectory = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, 10, 10, 500, 200, hWnd, NULL, g_hInst, NULL);
		//hTreeDirectory = CreateWindow(WC_TREEVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT, 10, 250, 100, 400, hWnd, NULL, g_hInst, NULL);
		hFolderUploadBtn = CreateWindow(TEXT("button"), "폴더등록", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)ID_hFolderUpload_Btn, g_hInst, NULL);
		//트리뷰

		// 리스트뷰
		/*COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)"곡명";
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
		SendMessage(hListViewDirectory, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);*/
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_hFolderUpload_Btn:
			GetWindowsDirectory(RootDir, MAX_PATH);
			BrowseFolder(hWnd, NULL, NULL, RootDir);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
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
	BROWSEINFO bi;

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
}


