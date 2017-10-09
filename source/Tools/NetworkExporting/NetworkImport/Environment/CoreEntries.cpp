#include "stdafx.h"
#include "CoreEntries.h"

#include "..\ImportManager\ImportManager.h"

#include "interface_idds.h"

IImportManager* CreateImportManager()
{
	CImportManager* pManager = new CImportManager();
	
	IImportManager* pManagerControl = NULL;
	pManager->QueryInterface(IDD_IImportManager, (void**)&pManagerControl);

	return pManagerControl;	
}

void ReleaseImportManager(IImportManager* pManager)
{
	if (pManager)
		delete pManager;
}

CString GetComponentName()
{
	return _T("NetworkImportManager");
}

CString GetComponentVersion()
{
	return _T("1.0.0.0");
}