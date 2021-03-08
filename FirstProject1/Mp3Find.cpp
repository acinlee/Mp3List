#include <windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void FileList(TCHAR* path);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Mp3List");

enum
{
	ID_hListView_File = 100,
	ID_hTreeView_Folder = 200,
	ID_hFile_Route_Combobox = 300
};

HWND hListView_File;
HWND hTreeView_Folder;
HWND hFile_Route_Combobox;

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

void FileList(TCHAR* path)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	TCHAR fname[MAX_PATH];
	BOOL bResult = TRUE;
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[MAX_PATH];
	TCHAR newpath[MAX_PATH];
	
	hSrch = FindFirstFile(path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE)
	{
		return;
	}
	_splitpath(path, drive, dir, NULL, NULL);
	
	while (bResult)
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, ".") && lstrcmp(wfd.cFileName, ".."))
			{
				wsprintf(newpath, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
				FileList(newpath);
			}
		}
		else
		{
			wsprintf(fname, "%s%s%s\\*.*", drive, dir, wfd.cFileName);
			SendMessage(hListView_File, LB_ADDSTRING, 0, (LPARAM)fname);
		}
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TVINSERTSTRUCT Mp3TreeViewInsert;
	LPTVINSERTSTRUCT Mp3ListViewInsert;

	switch(iMessage)
	{
	case WM_CREATE:
		InitCommonControls();
		hListView_File = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 10, 10, 600, 300, hWnd, NULL, g_hInst, NULL);
		hFile_Route_Combobox = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 400, 200, hWnd, (HMENU)1, g_hInst, NULL);
		hTreeView_Folder = CreateWindow(WC_TREEVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES, 10, 150, 400, 800, hWnd, NULL, g_hInst, NULL);


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
