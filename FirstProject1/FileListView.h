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
	FileListView();
	HWND Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	void FileListInsert(TCHAR* path, int file_num);

private:
	HWND m_hParent;
	HWND m_FileListView;
	HINSTANCE m_hInstance;

	//리스트뷰
	LVCOLUMN m_COL;
	LVITEM m_LI;

	//listview x, y, width, height 
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	//파일 개수
	int m_filenum;
};
#endif // !FileListViewHeader
