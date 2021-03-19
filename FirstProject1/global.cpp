#include "global.h"
#include <stdlib.h>
//LNK2001 에러 발생 해서 넣은 구문
/*
* LNK2001 에러가 나오는 경우는 해당하는 static 변수를 찾을 수 없기 때문
* 클래스 내부에 선언 해놓으면 메모리에 변수 할당 되며 이것을 기반으로 객체들이 이 변수를 공유
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
