#pragma once
#include "MainWindow.h"
#include <CommCtrl.h>
#include "global.h"
#pragma comment(lib, "comctl32.lib")

//todo : gobal.h �� ����� class ȭ
//extern HINSTANCE g_hInstance;
//todo : ������ �ʱ�ȭ�� ����ο��� �ʱ�ȭ �ϵ��� ����.
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
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//����, ���� ���� �� ������ �ٽ� �׸�, ����Ŭ�� ����
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
	//todo : �ʱ� ���� ��ġ(x, y, width, height��) �Ķ���ͷ� �и�
	m_folderTree.Create(hWnd, Global::get_hInstance(), 10, 100, 400, 200);
	m_setHomeFolderButton.Create(hWnd, Global::get_hInstance(), "���� ���", 440, 20, 100, 25, 100);
	//Edit box ��ſ� static text�� ��ü ����
	//FilePathEdit_Instance.Create(hWnd, Global::get_hInstance());
	m_filListView.Create(hWnd, Global::get_hInstance(), 410, 100, 420, 200);
	//todo : Create���� �ϵ��� ��ġ ����
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
		//������ �� �Ѱ� ���� this �����͸� �����Ͽ� ���� Ŭ���� ��� ���� �� ���
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