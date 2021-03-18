#ifndef FolderList_TreeView
#define FolderList_TreeView
#include <windows.h>
#include <CommCtrl.h>
#include <sstream>
#pragma comment(lib, "comctl32.lib")

class TreeView_FolderList
{
public:
	TreeView_FolderList();
	HWND Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height);
	void InsertRootFolder(TCHAR* path);
	void InsertFolderList(TCHAR* path, HTREEITEM hParent);

private:
	HWND m_ParentWnd;
	HWND m_hTreeFolerList;
	HINSTANCE m_hInstance;

	//트리뷰
	TVINSERTSTRUCT m_TI;
	HTREEITEM m_HTREE;

	//x, y, width, height
	int m_x;
	int m_y;
	int m_width;
	int m_height;

	//사용자 선택 폴더
	//TCHAR RootDir[MAX_PATH];

};
#endif // !FileList_TreeView
