#include "stdafx.h"
#include "CoreEntries.h"

#include "..\Manager\Manager.h"

#include "interface_idds.h"

IManagerControl* CreateNetworkTrainers()
{
	CManager* pManager = new CManager();
	
	IManagerControl* pManagerControl = NULL;
	pManager->QueryInterface(IDD_IManagerControl, (void**)&pManagerControl);

	return pManagerControl;	
}

void ReleaseNetworkTrainers(IManagerControl* pManager)
{
	if (pManager)
		delete pManager;
}

CString GetComponentName()
{
	return _T("NetworkTrainers");
}

CString GetComponentVersion()
{
	return _T("1.0.0.0b");
}