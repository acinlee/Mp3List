#pragma once
#include "FilePathEdit.h"

FilePathEdit::FilePathEdit()
{
	m_ParentWnd = NULL;
	m_FilePathEdit = NULL;
	m_hInstance = NULL;
	m_ID_FilePath_Edit = 200;
}

HWND FilePathEdit::Create(HWND hWnd, HINSTANCE hInstance)
{
	m_ParentWnd = hWnd;
	m_hInstance = hInstance;
	return (m_FilePathEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 400, 25, m_ParentWnd, (HMENU)m_ID_FilePath_Edit, m_hInstance, NULL));
}
