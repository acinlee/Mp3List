#pragma once
#ifndef FileListViewHeader
#define FileListViewHeader
#include <Windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

class FileListView {
public:
	HWND m_hParent;
	HWND m_FileListView;
	HINSTANCE m_hInstance;

	//¸®½ºÆ®ºä
	LVCOLUMN m_COL;
	LVITEM m_LI;
public:
	FileListView();
	HWND Create(HWND hWnd, HINSTANCE hInstance);
	void FileListClassificationInsert();
	void FileListInsert();

};
#endif // !FileListViewHeader
