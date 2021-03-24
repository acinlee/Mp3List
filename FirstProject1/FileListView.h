#pragma once
#ifndef FileListViewHeader
#define FileListViewHeader
#include <Windows.h>
#include <CommCtrl.h>
#include <vector>
#pragma comment(lib, "comctl32.lib")

class FileListView {
public:
	typedef struct 
	{
		char title[31];
		char artist[31];
		char year[5];
		char album[31];
	}SongInfo;

public:
	FileListView();
	void Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	void SongStructInsert(WCHAR* path);
	BOOL Mp3Info(WCHAR* filename, SongInfo* song);
	HWND getListView();
	BOOL FileListInsert();

private:
	HWND m_hParent;
	HWND m_FileListView;
	HINSTANCE m_hInstance;

	//����Ʈ��
	LVCOLUMN m_COL;
	LVITEM m_LI;

	//listview x, y, width, height 
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	std::vector<SongInfo> songs;
};
#endif // !FileListViewHeader
