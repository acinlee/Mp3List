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
	while (GetMessage(main.get_LMessage(), NULL, 0, 0))
	{
		TranslateMessage(main.get_LMessage());
		DispatchMessage(main.get_LMessage());
	}

	return (int)main.get_Message().wParam;
}