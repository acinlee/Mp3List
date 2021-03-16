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
	/*�Ϲ������� ������ ���ν����� static�̾�� �ϱ� ������ � Ŭ������ ��������� �η��� static
	�� ����ؾ� �Ѵ�. �� ������ Ŭ������ ��� �Լ����� ������ �ʰ� this�����͸� �Ű������� �ް� �Ǹ�
	�׷��� ������ WndProc�Լ��� �Ű������� �ϳ� �� �������ν� ���̻� ������ ���ν����� �ƴϰ� �ǹǷ� ������ ���� ���̴�.
	�׷��� ������ static ������ �ٿ���� �ϸ� CreateWindow�� return �� �� ������ �Ű������� this�� ���� �ؾ� �Ѵ�.
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

	//MainMessageProc �޽��� ó�� ����
	HWND m_hWnd;
	UINT m_iMessage;
	WPARAM m_wParam;
	LPARAM m_lParam;

private:
	TreeView_FolderList m_folderTree;
	//todo : MyButton���� �̸� ���� �� ����ȭ
	FolderRegisterBtn m_setHomeFolderButton;
	//todo  : ����
	FilePathEdit FilePathEdit_Instance;

	FileListView m_filListView;
	
	Mp3InfoWnd m_mp3InfoWnd;
};


#endif // !WinMainHeader

