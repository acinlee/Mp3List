#pragma once
#include "MainWindow.h"
#include <CommCtrl.h>
#include "global.h"
#pragma comment(lib, "comctl32.lib")

//todo : gobal.h 를 만들어 class 화
//extern HINSTANCE g_hInstance;
//todo : 생성자 초기화나 선언부에서 초기화 하도록 변경.
MainWindow::MainWindow():m_Main_Window(NULL), m_lpszClass(TEXT("default")), m_Message({ 0, }), 
m_WndClass({ 0, }), m_hWnd(NULL), m_iMessage(NULL), m_wParam(NULL), m_lParam(NULL)
{
}

void MainWindow::Create()
{
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	m_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WndClass.hInstance = Global::get_hInstance();
	m_WndClass.lpfnWndProc = WndProc;
	m_WndClass.lpszClassName = m_lpszClass;
	m_WndClass.lpszMenuName = NULL;
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//넓이, 높이 변경 시 윈도우 다시 그림, 더블클릭 지원
	RegisterClass(&m_WndClass);
	
	m_Main_Window = CreateWindow(m_lpszClass, m_lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, Global::get_hInstance(), this);
	ShowWindow(m_Main_Window, SW_SHOW);
}

LPMSG MainWindow::get_LMessage()
{
	return &m_Message;
}

MSG MainWindow::get_Message()
{
	return m_Message;
}

LRESULT MainWindow::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//todo : 초기 생성 위치(x, y, width, height값) 파라미터로 분리
	m_folderTree.Create(hWnd, Global::get_hInstance(), 10, 100, 400, 200);
	m_setHomeFolderButton.Create(hWnd, Global::get_hInstance(), "폴더 등록", 440, 20, 100, 25, 100);
	//Edit box 대신에 static text로 교체 예정
	//FilePathEdit_Instance.Create(hWnd, Global::get_hInstance());
	m_filListView.Create(hWnd, Global::get_hInstance(), 410, 100, 420, 200);
	//todo : Create에서 하도록 위치 변경
	return 0;
}

LRESULT MainWindow::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
	//case m_setHomeFolderButton.m_id:
		//todo : class naming -> FolderPicker
		/*FolderPathDecision folderPicker;
		if (folderPicker.BrowseFolder(hWnd, NULL, NULL, FilePathEdit_Instance.m_UserSelectFolder) == TRUE)
		{
			SetWindowText(FilePathEdit_Instance.m_FilePathEdit, FilePathEdit_Instance.m_UserSelectFolder);
			m_folderTree.InsertRootFolder(FilePathEdit_Instance.m_UserSelectFolder);
			m_filListView.FileListInsert(FilePathEdit_Instance.m_UserSelectFolder, m_filListView.file_num);
		}*/
		//Mp3InfoWnd_Instance.Create(m_hWnd, m_hInstance);
		return 0;
	}
	return 0;
}

LRESULT MainWindow::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


LRESULT MainWindow::OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
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
		return 0;
	case WM_NOTIFY:
		main->OnNotify(hWnd, wParam, lParam);
		break;
	case WM_DESTROY:
		main->OnDestroy(hWnd, wParam, lParam);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}