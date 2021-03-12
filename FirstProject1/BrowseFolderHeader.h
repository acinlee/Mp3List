#pragma once
#ifndef BrowseFolderHeader
#define BrowseFolderHeader
#include <Windows.h>

class FolderPathDecision
{
public:
	static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT iMessage, LPARAM lParam, LPARAM lpData);
	BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCSTR StartPath, TCHAR* szFolder);
};
#endif // !BrowseFolderHeader
