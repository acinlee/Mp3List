#ifndef h_FilePathEdit
#define h_FilePathEdit
#include <Windows.h>

class FilePathEdit
{
public:
	HWND m_ParentWnd;
	HWND m_FilePathEdit;
	HINSTANCE m_hInstance;
	int m_ID_FilePath_Edit;

public:
	FilePathEdit();
	HWND Create(HWND hWnd, HINSTANCE hInstance);
};
#endif 


