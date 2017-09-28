#include "StdAfx.h"
#include "..\NeuroLab.h"
#include ".\pluginsmanagercomponent.h"

#include "interface_idds.h"

CPluginsManagerComponent::CPluginsManagerComponent(void)
{
	bIsLoaded = false;
	
	csLibraryName = _T("PluginsMng.dll");

	hLibrary = NULL;

	pfnGetComponentName = NULL;
	pfnGetComponentVersion = NULL;

	pfnCreatePluginsManager = NULL;
	pfnReleasePluginsManager = NULL;

	pManagerControl = NULL;

	pAppController = NULL;
}

CPluginsManagerComponent::~CPluginsManagerComponent(void)
{
	if (bIsLoaded)
		UnloadComponent();
}

// IComponent declarations section	
bool CPluginsManagerComponent::LoadComponent()
{
	if (!VerifyWhetherExists())
		return false;

	bool bRet = true;

	hLibrary = LoadLibrary(csLibraryName);
	if (!hLibrary)
		return false;

	(FARPROC &)pfnGetComponentName = GetProcAddress(hLibrary, "GetComponentName");
	(FARPROC &)pfnGetComponentVersion = GetProcAddress(hLibrary, "GetComponentVersion");

	(FARPROC &)pfnCreatePluginsManager = GetProcAddress(hLibrary, "CreatePluginsManager");
	(FARPROC &)pfnReleasePluginsManager = GetProcAddress(hLibrary, "ReleasePluginsManager");

	if (pfnCreatePluginsManager)
	{
		pManagerControl = (*pfnCreatePluginsManager)();
		pManagerControl->SetAppFolder(((CNeuroLabApp*)AfxGetApp())->GetAppFolder());
		pManagerControl->SetAppController(pAppController);
		pManagerControl->InitializeManagerInstance();
		
		bIsLoaded = true;
	}

	return bRet;
}

bool CPluginsManagerComponent::UnloadComponent()
{
	bool bRet = true;
	bIsLoaded = false;

	if (pManagerControl)
	{
		pManagerControl->ReleaseManagerInstance();
		(*pfnReleasePluginsManager)(pManagerControl);
		pManagerControl = NULL;
	}

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
	}
	
	return bRet;
}

bool CPluginsManagerComponent::VerifyWhetherExists()
{
	bool bRet = true;
	return bRet;
}

CString CPluginsManagerComponent::GetComponentName()
{
	CString csComponentName = _T("");
	if (bIsLoaded)
	{		
		csComponentName = (*pfnGetComponentName)();
	} 
	return csComponentName;	
}

CString CPluginsManagerComponent::GetComponentVersion()
{
	CString csComponentVirsion = _T("");
	if (bIsLoaded)
	{		
		csComponentVirsion = (*pfnGetComponentVersion)();
	} 
	return csComponentVirsion;
}

CString CPluginsManagerComponent::GetStateStringWhenLoading()
{
	return _T("Loading Plugins Manager Component and installed plugins...");
}

void CPluginsManagerComponent::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// IObject declarations section	
CString CPluginsManagerComponent::GetClassString()
{
	return CString("CPluginsManagerComponent");
}

void CPluginsManagerComponent::QueryInterface(int iIDD, void ** ppvObject)
{
	*ppvObject = NULL;
	if (pManagerControl)
		pManagerControl->QueryInterface(iIDD, ppvObject);

	switch (iIDD)
	{
	case IDD_IComponent:
		*ppvObject = (IComponent*)this;
		break;
	case IDD_Component_IPluginsManager:
		*ppvObject = (IPluginsManagerComponent*)this;
		break;
	}
}