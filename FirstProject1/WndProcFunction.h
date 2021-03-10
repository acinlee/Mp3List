#ifndef WndProcFunction
#define WndProcFunction
#include "MainWindowHeader.h"
class WndProcFunction
{
public:
	LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
};
#endif // !MainFunction