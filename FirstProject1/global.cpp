#include "global.h"

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
