#include "StdAfx.h"
#include "..\NeuroLab.h"
#include ".\networktrainerscomponent.h"

#include "interface_idds.h"

CNetworkTrainersComponent::CNetworkTrainersComponent(void)
{
	bIsLoaded = false;
	
	csLibraryName = _T("NetworkTrainers.dll");

	hLibrary = NULL;

	pfnGetComponentName = NULL;
	pfnGetComponentVersion = NULL;

	pfnCreateNetworkTrainers = NULL;
	pfnReleaseNetworkTrainers = NULL;

	pManagerControl = NULL;

	pAppController = NULL;
}

CNetworkTrainersComponent::~CNetworkTrainersComponent(void)
{
	if (bIsLoaded)
		UnloadComponent();
}

// IComponent declarations section	
bool CNetworkTrainersComponent::LoadComponent()
{
	if (!VerifyWhetherExists())
		return false;

	bool bRet = true;

	hLibrary = LoadLibrary(csLibraryName);
	if (!hLibrary)
		return false;

	(FARPROC &)pfnGetComponentName = GetProcAddress(hLibrary, "GetComponentName");
	(FARPROC &)pfnGetComponentVersion = GetProcAddress(hLibrary, "GetComponentVersion");

	(FARPROC &)pfnCreateNetworkTrainers = GetProcAddress(hLibrary, "CreateNetworkTrainers");
	(FARPROC &)pfnReleaseNetworkTrainers = GetProcAddress(hLibrary, "ReleaseNetworkTrainers");

	if (pfnCreateNetworkTrainers)
	{
		pManagerControl = (*pfnCreateNetworkTrainers)();
		pManagerControl->SetAppFolder(((CNeuroLabApp*)AfxGetApp())->GetAppFolder());
		pManagerControl->SetAppController(pAppController);
		pManagerControl->InitializeManagerInstance();
		
		bIsLoaded = true;
	}

	return bRet;
}

bool CNetworkTrainersComponent::UnloadComponent()
{
	bool bRet = true;
	bIsLoaded = false;

	if (pManagerControl)
	{
		pManagerControl->ReleaseManagerInstance();
		(*pfnReleaseNetworkTrainers)(pManagerControl);
		pManagerControl = NULL;
	}

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
	}
	
	return bRet;
}

bool CNetworkTrainersComponent::VerifyWhetherExists()
{
	bool bRet = true;
	return bRet;
}

CString CNetworkTrainersComponent::GetComponentName()
{
	CString csComponentName = _T("");
	if (bIsLoaded)
	{		
		csComponentName = (*pfnGetComponentName)();
	} 
	return csComponentName;	
}

CString CNetworkTrainersComponent::GetComponentVersion()
{
	CString csComponentVirsion = _T("");
	if (bIsLoaded)
	{		
		csComponentVirsion = (*pfnGetComponentVersion)();
	} 
	return csComponentVirsion;
}

CString CNetworkTrainersComponent::GetStateStringWhenLoading()
{
	return _T("Loading Network Trainers Component...");
}

void CNetworkTrainersComponent::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// IObject declarations section	
CString CNetworkTrainersComponent::GetClassString()
{
	return CString("CNetworkTrainersComponent");
}

void CNetworkTrainersComponent::QueryInterface(int iIDD, void ** ppvObject)
{
	*ppvObject = NULL;
	if (pManagerControl)
		pManagerControl->QueryInterface(iIDD, ppvObject);

	switch (iIDD)
	{
	case IDD_IComponent:
		*ppvObject = (IComponent*)this;
		break;
	case IDD_Component_INetworkTrainers:
		*ppvObject = (INetworkTrainersComponent*)this;
		break;
	}
}