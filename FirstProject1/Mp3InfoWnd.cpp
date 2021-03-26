#include "Mp3InfoWnd.h"
#include "global.h"

Mp3InfoWnd::Mp3InfoWnd():m_hDlg(NULL), m_iMessage(NULL), m_wParam(NULL), m_lParam(NULL)
{
}

void Mp3InfoWnd::Create(HWND hWnd, HINSTANCE hInstance)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Mp3DlgProc);
}

void Mp3InfoWnd::setText(const char* title, const char* artist, const char* year, const char* album)
{
	SetDlgItemText(m_hDlg, IDC_TITLE, Global::toLPWSTR(title));
}

void OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
}

BOOL CALLBACK Mp3InfoWnd::Mp3DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//static Mp3InfoWnd* mp3;
	switch (iMessage)
	{
	case WM_INITDIALOG:
		
		//mp3->OnInitDialog(hDlg, wParam, lParam);
		//SetDlgItemText(hDlg, IDC_TITLE, L"hello");
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


