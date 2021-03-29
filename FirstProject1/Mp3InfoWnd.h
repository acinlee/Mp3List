#pragma once
#ifndef Mp3InfoWndHeader
#define Mp3InfoWndHeader
#include <Windows.h>
#include "resource.h"
#include <string>

class Mp3InfoWnd
{
public:
	Mp3InfoWnd(std::wstring title, std::wstring artist, std::wstring year, std::wstring album);
	void Create(HWND hWnd, HINSTANCE hInstance);
	void setText(LPWSTR title, LPWSTR artist, LPWSTR year, LPWSTR album);
	void init(std::wstring title);
	static BOOL CALLBACK Mp3DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	std::wstring m_title;
	std::wstring m_artist;
	std::wstring m_year;
	std::wstring m_album;
	
};

#endif // !
