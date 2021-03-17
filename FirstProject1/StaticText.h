#pragma once
#ifndef h_StaticText
#define h_StaticText
#include <Windows.h>

class StaticText
{
public:
	StaticText();
	HWND Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	
	//path getter, setter
	TCHAR* get_path();
	void set_path(TCHAR path);

	//statictext �ڵ� getter
	HWND get_statictext();

private:
	HWND m_Parent;
	HWND m_StaticText;
	HINSTANCE m_hInstance;
	
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	//���� ���
	TCHAR m_path;
};
#endif // !staticTextFilePath
