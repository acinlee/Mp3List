#pragma once
#ifndef FileListViewHeader
#define FileListViewHeader
#include <string.h>
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#pragma comment(lib, "comctl32.lib")

class FileListView {
public:
	HWND m_hParent;
	HWND m_FileListView;
	HINSTANCE m_hInstance;

	//리스트뷰
	LVCOLUMN m_COL;
	LVITEM m_LI;

	//파일 개수
	int file_num;
public:
	FileListView();
	HWND Create(HWND hWnd, HINSTANCE hInstance);
	void FileListClassificationInsert();
	void FileListInsert(TCHAR* path, int file_num);

};
#endif // !FileListViewHeader
