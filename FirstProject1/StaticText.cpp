#include "StaticText.h"

StaticText::StaticText() :m_Parent(NULL), m_StaticText(NULL), m_hInstance(NULL),
m_x(0), m_y(0), m_width(0), m_height(0)
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

	return (m_StaticText = CreateWindow("static", NULL, WS_CHILD | WS_VISIBLE, x, y, width, height, m_Parent, (HMENU)-1, m_hInstance, NULL));
}