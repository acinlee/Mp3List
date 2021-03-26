#pragma once
#ifndef Mp3InfoWndHeader
#define Mp3InfoWndHeader
#include <Windows.h>
#include "resource.h"
class Mp3InfoWnd
{
public:
	Mp3InfoWnd();
	void Create(HWND hWnd, HINSTANCE hInstance);
	static BOOL CALLBACK Mp3DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void setText(const char*title, const char *artist, const char *year, const char* album);
	void OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
private:
	HWND m_hDlg;
	UINT m_iMessage;
	WPARAM m_wParam;
	LPARAM m_lParam;
};

#endif // !
