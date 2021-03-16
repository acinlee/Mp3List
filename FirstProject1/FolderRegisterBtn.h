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

	//버튼 x, y, width, height 
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	//버튼 이름
	LPCSTR m_name;

	//버튼 ID
	int m_id;
};
#endif // !FolderRegisterBtn.h
