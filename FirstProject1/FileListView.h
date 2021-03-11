#pragma once
#ifndef FileListViewHeader
#define FileListViewHeader
#include <Windows.h>
class FileListView {
public:
	HWND m_hParent;
	HWND m_FileListView;
	HINSTANCE m_hInstance;

public:
	FileListView();
	HWND Create(HWND hWnd, HINSTANCE hInstance);
};
#endif // !FileListViewHeader
