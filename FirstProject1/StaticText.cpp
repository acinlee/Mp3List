#include "StaticText.h"
#include "global.h"

StaticText::StaticText() :m_Parent(NULL), m_StaticText(NULL), m_hInstance(NULL),
m_x(0), m_y(0), m_width(0), m_height(0), m_path(NULL)
{
}

HWND StaticText::Create(HWND hWnd, HINSTANCE hInstance, int x, int y, int width, int height)
{
	m_Parent = hWnd;
	m_hInstance = hInstance;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	return (m_StaticText = CreateWindow(L"static", NULL, WS_CHILD | WS_VISIBLE, x, y, width, height, m_Parent, NULL, m_hInstance, NULL));
}

WCHAR* StaticText::get_path()
{
	return &m_path;
}

void StaticText::set_path(WCHAR path)
{
	m_path = path;
}

HWND StaticText::get_statictext()
{
	return m_StaticText;
}
