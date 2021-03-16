#include "MainWindow.h"
#include "global.h"
#include <windows.h>

//extern HINSTANCE g_hInstance;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	InitCommonControls();
	Global global;
	//hInstance를 가지고 있는 Global class 선언
	global.set_hInstance(hInstance);
	
	//main_window.Create();
	MainWindow main;
	main.Create();
	while (GetMessage(&main.m_Message, NULL, 0, 0))
	{
		TranslateMessage(&main.m_Message);
		DispatchMessage(&main.m_Message);
	}

	return (int)main.m_Message.wParam;
}