#pragma once
#include "MainWindowHeader.h"
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

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
	
	m_Main_Window = CreateWindow(m_lpszClass, m_lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, m_hInstance, this);
	ShowWindow(m_Main_Window, m_nCmdShow);
}

LRESULT MainWindow::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	TreeView_FolderList_Instance.Create(hWnd, m_hInstance);
	TreeView_FolderList_Instance.InsertFolderList();
	FolderRegisterBtn_Instance.Create(hWnd, m_hInstance);
	FilePathEdit_Instance.Create(hWnd, m_hInstance);
	FileListView_Instance.Create(hWnd, m_hInstance);
	FileListView_Instance.FileListInsert();
	return 0;
}


LRESULT MainWindow::OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT MainWindow::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
	case FolderRegisterBtn::m_ID_Btn:
		if (FolderPathDecision_Instance.BrowseFolder(hWnd, NULL, NULL, FilePathEdit_Instance.m_UserSelectFolder) == TRUE)
		{
			SetWindowText(FilePathEdit_Instance.m_FilePathEdit, FilePathEdit_Instance.m_UserSelectFolder);
		}
	}
	return 0;
}

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static MainWindow* main;
	switch (iMessage)
	{
	case WM_CREATE:
		//생성될 때 넘겨 받은 this 포인터를 보관하여 추후 클래스 멤버 참조 시 사용
		main = (MainWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		main->OnCreate(hWnd, wParam, lParam);
		return 0;
	case WM_COMMAND:
		main->OnCommand(hWnd, wParam, lParam);
		return FALSE;
	case WM_DESTROY:
		main->OnDestroy(hWnd, wParam, lParam);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}