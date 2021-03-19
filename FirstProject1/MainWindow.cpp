#pragma once
#include "MainWindow.h"
#include <CommCtrl.h>
#include <SHLOBJ.H>
#include "global.h"
#pragma comment(lib, "comctl32.lib")

//todo : ������ �ʱ�ȭ�� ����ο��� �ʱ�ȭ �ϵ��� ����.
MainWindow::MainWindow():m_Main_Window(NULL), m_lpszClass(TEXT("default")), m_Message({ 0, }), 
m_WndClass({ 0, }), m_hWnd(NULL), m_iMessage(NULL), m_wParam(NULL), m_lParam(NULL)
{
}

void MainWindow::Create()
{
	setlocale(LC_ALL, "");
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
	m_folderTree.Create(hWnd, Global::get_hInstance(), 10, 100, 400, 200);
	m_setHomeFolderButton.Create(hWnd, Global::get_hInstance(), L"���� ����", 440, 20, 100, 25, SET_HOME_FOLDER_BTN);
	m_FilePath.Create(hWnd, Global::get_hInstance(), 10, 20, 400, 25);
	m_filListView.Create(hWnd, Global::get_hInstance(), 410, 100, 600, 200);
	return 0;
}

LRESULT MainWindow::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
	case SET_HOME_FOLDER_BTN:
		if (BrowseFolder(hWnd, NULL, NULL, m_FilePath.get_path()) == TRUE)
		{
			SetWindowText(m_FilePath.get_statictext(), m_FilePath.get_path());
			m_folderTree.InsertRootFolder(m_FilePath.get_path());
			m_filListView.FileListInsert(m_FilePath.get_path());
		}
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

int CALLBACK MainWindow::BrowseCallbackProc(HWND hWnd, UINT iMessage, LPARAM lParam, LPARAM lpData)
{
	switch (iMessage)
	{
	case BFFM_INITIALIZED:
		if (lpData != NULL)
		{
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL MainWindow::BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCSTR StartPath, TCHAR* szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi = { 0, };

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL) {
		return FALSE;
	}
	SHGetPathFromIDList(pidl, szFolder);

	if (SHGetMalloc(&pMalloc) != NOERROR) {
		return FALSE;
	}
	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
}

