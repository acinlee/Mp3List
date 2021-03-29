#include "Mp3InfoWnd.h"
#include "global.h"



Mp3InfoWnd::Mp3InfoWnd(std::wstring title, std::wstring artist, std::wstring year, std::wstring album):m_title(title), m_artist(artist),
m_year(year), m_album(album)
{
}

void Mp3InfoWnd::Create(HWND hWnd, HINSTANCE hInstance)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Mp3DlgProc, reinterpret_cast<LPARAM>(this));

}
void Mp3InfoWnd::init(std::wstring title)
{
	m_title = title;
}

BOOL CALLBACK Mp3InfoWnd::Mp3DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static Mp3InfoWnd* mp3 = nullptr;
	switch (iMessage)
	{
	case WM_INITDIALOG:
		mp3 = reinterpret_cast<Mp3InfoWnd*>(lParam);
		SetDlgItemText(hDlg, IDC_TITLE, mp3->m_title.c_str());
		SetDlgItemText(hDlg, IDC_ARTIST, mp3->m_artist.c_str());
		SetDlgItemText(hDlg, IDC_YEAR, mp3->m_year.c_str());
		SetDlgItemText(hDlg, IDC_ALBUM , mp3->m_album.c_str());
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


