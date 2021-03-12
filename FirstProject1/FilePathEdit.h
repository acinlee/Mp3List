#ifndef h_FilePathEdit
#define h_FilePathEdit
#include <Windows.h>

class FilePathEdit
{
public:
	HWND m_ParentWnd;
	HWND m_FilePathEdit;
	HINSTANCE m_hInstance;
	TCHAR m_UserSelectFolder[MAX_PATH];

public:
	static const int m_ID_FilePath_Edit = 200;

public:
	FilePathEdit();
	HWND Create(HWND hWnd, HINSTANCE hInstance);
};
#endif 


