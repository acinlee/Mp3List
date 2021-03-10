#ifndef WinMainHeader
#define WinMainHeader
#include <windows.h>
class MainWindow
{
public:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	PSTR m_lpCmdLine;
	INT m_nCmdShow;
	HWND m_Main_Window;
	LPCTSTR m_lpszClass;
	MSG m_Message;
	WNDCLASS m_WndClass;
public:
	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdSow);
	~MainWindow();
	void MainWindowCreate();
private:
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
#endif // !WinMainHeader

