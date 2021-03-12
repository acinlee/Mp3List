#include "BrowseFolderHeader.h"
#include <SHLOBJ.H>
int CALLBACK FolderPathDecision::BrowseCallbackProc(HWND hWnd, UINT iMessage, LPARAM lParam, LPARAM lpData)
{
	switch (iMessage) {
	case BFFM_INITIALIZED:
		if (lpData != NULL) {
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL FolderPathDecision::BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCSTR StartPath, TCHAR* szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi = { 0, };

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL) {
		return FALSE;
	}
	SHGetPathFromIDList(pidl, szFolder);

	if (SHGetMalloc(&pMalloc) != NOERROR) {
		return FALSE;
	}
	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
}

