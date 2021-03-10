#ifndef MainWindowHeader
#define MainWindowHeader
#include <windows.h>
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

	//MainMessageProc �޽��� ó�� ����
	HWND m_hWnd;
	UINT m_iMessage;
	WPARAM m_wParam;
	LPARAM m_lParam;

public:
	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdSow);
	/*�Ϲ������� ������ ���ν����� static�̾�� �ϱ� ������ � Ŭ������ ��������� �η��� static
	* �� ����ؾ� �Ѵ�. �� ������ Ŭ������ ��� �Լ����� ������ �ʰ� this�����͸� �Ű������� �ް� �Ǹ� 
	�׷��� ������ WndProc�Լ��� �Ű������� �ϳ� �� �������ν� ���̻� ������ ���ν����� �ƴϰ� �ǹǷ� ������ ���� ���̴�.
	�׷��� ������ static ������ �ٿ���� �ϸ� CreateWindow�� return �� �� ������ �Ű������� this�� ���� �ؾ� �Ѵ�.
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void Create();
private:
};


#endif // !WinMainHeader

