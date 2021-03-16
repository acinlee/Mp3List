#ifndef h_FolderRegisterBtn
#define h_FolderRegisterBtn
#include <windows.h>
#include <string>

class MyButton
{
public:
	MyButton();
	HWND Create(HWND hWnd, HINSTANCE hInstance, LPCSTR name, int x, int y, int width, int height, int id);

private:
	HWND m_ParentWnd;
	HWND m_Btn;
	HINSTANCE m_hInstance;

	//��ư x, y, width, height 
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	//��ư �̸�
	LPCSTR m_name;

	//��ư ID
	int m_id;
};
#endif // !FolderRegisterBtn.h
