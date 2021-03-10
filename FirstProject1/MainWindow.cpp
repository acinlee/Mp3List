#include "MainWindowHeader.h"

MainWindow::MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdSow)
{
	m_hInstance = hInstance;
	m_hPrevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdSow;
	m_Main_Window = NULL;
	m_lpszClass = TEXT("default");
	m_Message = { 0, };
	m_WndClass = { 0, };

	m_hWnd = NULL;
	m_iMessage = 0;
	m_wParam = NULL;
	m_lParam = NULL;
}

void MainWindow::Create()
{
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	m_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WndClass.hInstance = m_hInstance;
	m_WndClass.lpfnWndProc = WndProc;
	m_WndClass.lpszClassName = m_lpszClass;
	m_WndClass.lpszMenuName = NULL;
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;//넓이, 높이 변경 시 윈도우 다시 그림
	RegisterClass(&m_WndClass);

	m_Main_Window = CreateWindow(m_lpszClass, m_lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, m_hInstance, NULL);
	ShowWindow(m_Main_Window, m_nCmdShow);
}

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}