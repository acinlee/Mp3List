#ifndef MainWindowHeader
#define MainWindowHeader
#include <windows.h>
#include <SHLOBJ.H>
#include "FolderList_TreeView.h"
#include "FolderRegisterBtn.h"
#include "FilePathEdit.h"
#include "FileListView.h"
#include "BrowseFolderHeader.h"
#include "Mp3InfoWndHeader.h"
#include "resource.h"

class MainWindow
{
public:
	MainWindow();
	/*일반적으로 윈도우 프로시져는 static이어야 하기 때문에 어떤 클래스의 멤버변수로 두려면 static
	을 사용해야 한다. 그 이유는 클래스의 멤버 함수들은 보이지 않게 this포인터를 매개변수로 받게 되며
	그렇기 때문에 WndProc함수가 매개변수를 하나 더 받음으로써 더이상 윈도우 프로시저가 아니게 되므로 오류가 나는 것이다.
	그렇기 때문에 static 선언을 붙여줘야 하며 CreateWindow을 return 할 시 마지막 매개변수로 this를 전달 해야 한다.
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void Create();
	MSG m_Message;
	MSG get_Message();
private:
	LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	HWND m_Main_Window;
	LPCTSTR m_lpszClass;
	//MSG m_Message;
	WNDCLASS m_WndClass;

	//MainMessageProc 메시지 처리 관련
	HWND m_hWnd;
	UINT m_iMessage;
	WPARAM m_wParam;
	LPARAM m_lParam;

private:
	TreeView_FolderList m_folderTree;
	//todo : MyButton으로 이름 변경 및 공통화
	FolderRegisterBtn m_setHomeFolderButton;
	//todo  : 제거
	FilePathEdit FilePathEdit_Instance;

	FileListView m_filListView;
	
	Mp3InfoWnd m_mp3InfoWnd;
};


#endif // !WinMainHeader

