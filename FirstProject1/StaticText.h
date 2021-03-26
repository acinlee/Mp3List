#pragma once
#ifndef h_StaticText
#define h_StaticText
#include <Windows.h>

class StaticText
{
public:
	StaticText();
	void Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	
	//path getter, setter
	WCHAR* get_path();
	void set_path(WCHAR *path);

	//statictext 핸들 getter
	HWND get_statictext();

private:
	HWND m_Parent;
	HWND m_StaticText;
	HINSTANCE m_hInstance;
	
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	//폴더 경로
	//path에 그냥 문자열을 넣어서 오류가 생겼었음...
	WCHAR m_path[MAX_PATH] = {0,};
};
#endif // !staticTextFilePath
