#pragma once
#ifndef Mp3InfoWndHeader
#define Mp3InfoWndHeader
#include <Windows.h>
#include "resource.h"
class Mp3InfoWnd
{
public:
	void Create(HWND hWnd, HINSTANCE hInstance);
	static BOOL CALLBACK Mp3DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

#endif // !
