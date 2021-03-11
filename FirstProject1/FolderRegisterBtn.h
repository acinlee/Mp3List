#ifndef h_FolderRegisterBtn
#define h_FolderRegisterBtn
#include <windows.h>

class FolderRegisterBtn
{
public:
	HWND m_ParentWnd;
	HWND m_FolderRegisterBtn;
	HINSTANCE m_hInstance;

public:
	static const int m_ID_Btn = 100;

public:
	FolderRegisterBtn();
	HWND Create(HWND hWnd, HINSTANCE hInstance);

};
#endif // !FolderRegisterBtn.h
