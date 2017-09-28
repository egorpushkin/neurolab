#include "StdAfx.h"
#include ".\builderelementscomponent.h"

#include "interface_idds.h"

CBuilderElementsComponent::CBuilderElementsComponent(void)
{
	bIsLoaded = false;
	
	csLibraryName = _T("BuilderElements.dll");

	hLibrary = NULL;

	pfnGetComponentName = NULL;
	pfnGetComponentVersion = NULL;

	pfnCreateBuilderManager = NULL;
	pfnReleaseBuilderManager = NULL;

	pManagerControl = NULL;

	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);		
}

CBuilderElementsComponent::~CBuilderElementsComponent(void)
{
	if (bIsLoaded)
		UnloadComponent();
}


// IComponent implementations section	
bool CBuilderElementsComponent::LoadComponent()
{
	if (!VerifyWhetherExists())
		return false;

	bool bRet = true;

	hLibrary = LoadLibrary(csLibraryName);
	if (!hLibrary)
		return false;

	(FARPROC &)pfnGetComponentName = GetProcAddress(hLibrary, "GetComponentName");
	(FARPROC &)pfnGetComponentVersion = GetProcAddress(hLibrary, "GetComponentVersion");

	(FARPROC &)pfnCreateBuilderManager = GetProcAddress(hLibrary, "CreateBuilderManager");
	(FARPROC &)pfnReleaseBuilderManager = GetProcAddress(hLibrary, "ReleaseBuilderManager");

	pManagerControl = (*pfnCreateBuilderManager)();
	pManagerControl->SetAppFolder(csAppFolder);
	pManagerControl->SetAppController(NULL);
	pManagerControl->InitializeManagerInstance();
	
	bIsLoaded = true;
	return bRet;
}

bool CBuilderElementsComponent::UnloadComponent()
{
	bool bRet = true;
	bIsLoaded = false;

	if (pManagerControl)
	{
		pManagerControl->ReleaseManagerInstance();
		(*pfnReleaseBuilderManager)(pManagerControl);
		pManagerControl = NULL;
	}

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
	}
	
	return bRet;
}

bool CBuilderElementsComponent::VerifyWhetherExists()
{
	bool bRet = true;
	return bRet;
}

CString CBuilderElementsComponent::GetComponentName()
{
	CString csComponentName = _T("");
	if (bIsLoaded)
	{		
		csComponentName = (*pfnGetComponentName)();
	} 
	return csComponentName;	
}

CString CBuilderElementsComponent::GetComponentVersion()
{
	CString csComponentVirsion = _T("");
	if (bIsLoaded)
	{		
		csComponentVirsion = (*pfnGetComponentVersion)();
	} 
	return csComponentVirsion;
}

CString CBuilderElementsComponent::GetStateStringWhenLoading()
{
	return _T("Loading Builder Elements Component...");
}

// IObject declarations section	
CString CBuilderElementsComponent::GetClassString()
{
	return _T("CBuilderElementsComponent");
}

void CBuilderElementsComponent::QueryInterface(int iIDD, void ** ppvObject)
{
	*ppvObject = NULL;
	if (pManagerControl)
		 pManagerControl->QueryInterface(iIDD, ppvObject);

	switch (iIDD)
	{
	case IDD_IComponent:
		*ppvObject = (IComponent*)this;
		break;
	case IDD_Component_IBuilderElements:
		*ppvObject = (IBuilderElementsComponent*)this;
		break;
	}
}
