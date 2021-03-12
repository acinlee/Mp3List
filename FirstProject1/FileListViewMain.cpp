#include "FileListView.h"
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

FileListView::FileListView()
{
	m_hParent = NULL;
	m_FileListView = NULL;
	m_hInstance = NULL;

	//¸®½ºÆ®ºä
	m_COL = { 0, };
	m_LI = { 0, };
}

HWND FileListView::Create(HWND hWnd, HINSTANCE hInstance)
{
	m_hParent = hWnd;
	m_hInstance = hInstance;
	return (m_FileListView = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, 410, 100, 620, 200, m_hParent, NULL, m_hInstance, NULL));
}

void FileListView::FileListClassificationInsert()
{
	m_COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	m_COL.fmt = LVCFMT_LEFT;
	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("°î¸í");
	m_COL.iSubItem = 0;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 0, (LPARAM)&m_COL);

	m_COL.cx = 20;
	m_COL.pszText = const_cast<char*>("#");
	m_COL.iSubItem = 1;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 1, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("Á¦¸ñ");
	m_COL.iSubItem = 2;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 2, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("Âü¿©À½¾Ç°¡");
	m_COL.iSubItem = 3;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 3, (LPARAM)&m_COL);

	m_COL.cx = 150;
	m_COL.pszText = const_cast<char*>("¾Ù¹ü");
	m_COL.iSubItem = 4;
	SendMessage(m_FileListView, LVM_INSERTCOLUMN, 4, (LPARAM)&m_COL);
}