#pragma once
#ifndef global_hInstance
#define global_hInstace
#include <Windows.h>

//두가지 방법
/*
* 1. extern Global global; -> 인스턴스 자체를 전역으로 만듬
* 2. 클래스 상에서 static으로 선언하는 방법
* % 애초에 hInstance는 한정적인 부분에서 setter을 호출 따라서 friend 클래스를 만들어서 사용할 수 있는 부분을 세세하게 만들 수 있음.
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
