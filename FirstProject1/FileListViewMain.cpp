#include "FileListView.h"
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

FileListView::FileListView()
{
	m_hParent = NULL;
	m_FileListView = NULL;
	m_hInstance = NULL;
}

HWND FileListView::Create(HWND hWnd, HINSTANCE hInstance)
{
	m_hParent = hWnd;
	m_hInstance = hInstance;
	return (m_FileListView = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, 410, 100, 620, 200, m_hParent, NULL, m_hInstance, NULL));
}