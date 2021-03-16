#pragma once
#ifndef global_hInstance
#define global_hInstace
#include <Windows.h>

//�ΰ��� ���
/*
* 1. extern Global global; -> �ν��Ͻ� ��ü�� �������� ����
* 2. Ŭ���� �󿡼� static���� �����ϴ� ���
* % ���ʿ� hInstance�� �������� �κп��� setter�� ȣ�� ���� friend Ŭ������ ���� ����� �� �ִ� �κ��� �����ϰ� ���� �� ����.
*/
class Global
{
public:
	Global();
	static void set_hInstance(HINSTANCE hInstance);
	static HINSTANCE get_hInstance();
private:
	static HINSTANCE g_hInstance;
};
#endif // !global_hInstance
