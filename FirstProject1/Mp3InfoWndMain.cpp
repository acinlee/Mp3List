#include "Mp3InfoWndHeader.h"

void Mp3InfoWnd::Create(HWND hWnd, HINSTANCE hInstance)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Mp3DlgProc);
}

BOOL CALLBACK Mp3InfoWnd::Mp3DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
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
