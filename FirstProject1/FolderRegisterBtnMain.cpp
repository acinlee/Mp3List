#pragma once
#include "FolderRegisterBtn.h"

FolderRegisterBtn::FolderRegisterBtn()
{
	m_ParentWnd = NULL;
	m_FolderRegisterBtn = NULL;
	m_hInstance = NULL;
}

HWND FolderRegisterBtn::Create(HWND hWnd, HINSTANCE hInstance)
{
	m_ParentWnd = hWnd;
	m_hInstance = hInstance;
	return (m_FolderRegisterBtn = CreateWindow(TEXT("button"), "폴더등록", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 440, 20, 100, 25, m_ParentWnd, (HMENU)m_ID_Btn, m_hInstance, NULL));
}