#ifndef MainWindowHeader
#define MainWindowHeader
#include <windows.h>
#include <SHLOBJ.H>
#include "FolderList_TreeView.h"
#include "FolderRegisterBtn.h"
#include "FileListView.h"
#include "StaticText.h"
#include "resource.h"
#include <locale.h>
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
	static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT iMessage, LPARAM lParam, LPARAM lpData);
	BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCSTR StartPath, TCHAR* szFolder);
	void Create();
	LPMSG get_LMessage();
	MSG get_Message();
private:
	LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	HWND m_Main_Window;
	LPCTSTR m_lpszClass;
	MSG m_Message;
	WNDCLASS m_WndClass;

	//MainMessageProc �޽��� ó�� ����
	HWND m_hWnd;
	UINT m_iMessage;
	WPARAM m_wParam;
	LPARAM m_lParam;

private:
	TreeView_FolderList m_folderTree;
	MyButton m_setHomeFolderButton;
	StaticText m_FilePath;
	FileListView m_filListView;

};


#endif // !WinMainHeader

