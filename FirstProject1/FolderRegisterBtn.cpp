#pragma once
#include "FolderRegisterBtn.h"

MyButton::MyButton() :m_ParentWnd(NULL), m_Btn(NULL), m_hInstance(NULL), m_name(NULL), m_x(0), m_y(0),
m_width(0), m_height(0), m_id(0)
{
}

HWND MyButton::Create(HWND hWnd, HINSTANCE hInstance, LPCSTR name, int x, int y, int width, int height, int id)
{
	m_ParentWnd = hWnd;
	m_hInstance = hInstance;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_id = id;
	m_name = name;

	return (m_Btn = CreateWindow("button", name, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height, m_ParentWnd, (HMENU)id, m_hInstance, NULL));
}