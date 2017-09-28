#include "stdafx.h"
#include "CoreEntries.h"

#include "..\Manager\Manager.h"

#include "..\..\Common\interface_idds.h"

IManagerControl* CreateBuilderManager()
{
	CManager * pManager = new CManager();
	
	IManagerControl * pManagerControl = NULL;
	pManager->QueryInterface(IDD_IManagerControl, (void**)&pManagerControl);

	return pManagerControl;	
}

void ReleaseBuilderManager(IManagerControl* pManager)
{
	if (pManager)
		delete pManager;
}

CString GetComponentName()
{
	return _T("BuilderElements");
}

CString GetComponentVersion()
{
	return _T("1.0.0.0b");
}