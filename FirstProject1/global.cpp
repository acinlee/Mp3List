#include "global.h"
#include <stdlib.h>
//LNK2001 ���� �߻� �ؼ� ���� ����
/*
* LNK2001 ������ ������ ���� �ش��ϴ� static ������ ã�� �� ���� ����
* Ŭ���� ���ο� ���� �س����� �޸𸮿� ���� �Ҵ� �Ǹ� �̰��� ������� ��ü���� �� ������ ����
*/
HINSTANCE Global::g_hInstance = NULL;

Global::Global()
{
}

HINSTANCE Global::get_hInstance()
{
	return g_hInstance;
}

void Global::set_hInstance(HINSTANCE hInstance)
{
	g_hInstance = hInstance;
}

LPWSTR Global::toLPWSTR(const char *text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wtext = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, text, size - 1);
	return wtext;
}
