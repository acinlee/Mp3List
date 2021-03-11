#ifndef MainWindowHeader
#define MainWindowHeader
#include <windows.h>
#include <SHLOBJ.H>
#include "FolderList_TreeView.h"
#include "FolderRegisterBtn.h"
#include "FilePathEdit.h"
#include "FileListView.h"

class MainWindow
{
public:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	PSTR m_lpCmdLine;
	INT m_nCmdShow;
	HWND m_Main_Window;
	LPCTSTR m_lpszClass;
	MSG m_Message;
	WNDCLASS m_WndClass;

	//MainMessageProc 메시지 처리 관련
	HWND m_hWnd;
	UINT m_iMessage;
	WPARAM m_wParam;
	LPARAM m_lParam;

public:
	TreeView_FolderList TreeView_FolderList_Instance;
	FolderRegisterBtn FolderRegisterBtn_Instance;
	FilePathEdit FilePathEdit_Instance;
	FileListView FileListView_Instance;

public:
	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdSow);
	/*일반적으로 윈도우 프로시져는 static이어야 하기 때문에 어떤 클래스의 멤버변수로 두려면 static
	을 사용해야 한다. 그 이유는 클래스의 멤버 함수들은 보이지 않게 this포인터를 매개변수로 받게 되며 
	그렇기 때문에 WndProc함수가 매개변수를 하나 더 받음으로써 더이상 윈도우 프로시저가 아니게 되므로 오류가 나는 것이다.
	그렇기 때문에 static 선언을 붙여줘야 하며 CreateWindow을 return 할 시 마지막 매개변수로 this를 전달 해야 한다.
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void Create();
	LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);

	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder);
};


#endif // !WinMainHeader

