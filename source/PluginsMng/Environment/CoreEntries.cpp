#include "stdafx.h"
#include "CoreEntries.h"

#include "..\Manager\Manager.h"

#include "..\..\Common\interface_idds.h"

IManagerControl * CreatePluginsManager()
{
	CManager * pManager = new CManager();
	
	IManagerControl * pManagerControl = NULL;
	pManager->QueryInterface(IDD_IManagerControl, (void**)&pManagerControl);

	return pManagerControl;
}

void ReleasePluginsManager(IManagerControl * pManagerControl)
{
	if (pManagerControl)
		delete pManagerControl;
}

CString	GetComponentName()
{
	return _T("PluginsManager");
}

CString	GetComponentVersion()
{
	return _T("1.0.0.0b");
}