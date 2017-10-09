//	This code is a part of Network Importing SDK.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ImportManagerComponent.cpp
//	Description: Import manager component implementation.

#include "StdAfx.h"
#include "ImportManagerComponent.h"

#include "Interface_idds.h"

CImportManagerComponent::CImportManagerComponent()
	: bIsInitialized(false)
	, csNetworkImportLib(_T("NetworkImport.dll"))
	, hLibrary(NULL)
	, pfnGetComponentName(NULL)
	, pfnGetComponentVersion(NULL)
	, pfnCreateImportManager(NULL)
	, pfnReleaseImportManager(NULL)
{
	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);		
}

CImportManagerComponent::~CImportManagerComponent()
{
	UnloadComponent();
}

IImportManager* CImportManagerComponent::GetImportManager()
{
	if (!bIsInitialized)
		return NULL;

	IImportManager* pImportManager = (*pfnCreateImportManager)();
	pImportManager->InitializeManager();

	return pImportManager;
}

void CImportManagerComponent::ReleaseImportManager(IImportManager* pManager)
{
	if (pManager)
	{
		(*pfnReleaseImportManager)(pManager);
	}
}

bool CImportManagerComponent::IsLoaded()
{
	return bIsInitialized;
}

CString CImportManagerComponent::GetAppFolder()
{
	return csAppFolder;	
}

// IComponent implementations section	
bool CImportManagerComponent::LoadComponent()
{
	if (!VerifyWhetherExists())
		return false;

	CString tmLibFile = 
		csAppFolder + 
		CString(_T("\\Exports\\")) + 
		csNetworkImportLib;

	hLibrary = LoadLibrary(tmLibFile);
	if (!hLibrary)
		return false;

	(FARPROC &)pfnGetComponentName = GetProcAddress(hLibrary, "GetComponentName");
	(FARPROC &)pfnGetComponentVersion = GetProcAddress(hLibrary, "GetComponentVersion");

	if (!pfnGetComponentName || !pfnGetComponentVersion)
	{
		UnloadComponent();
		return false;
	}

	(FARPROC &)pfnCreateImportManager = GetProcAddress(hLibrary, "CreateImportManager");
	(FARPROC &)pfnReleaseImportManager = GetProcAddress(hLibrary, "ReleaseImportManager");

	if (!pfnCreateImportManager || !pfnReleaseImportManager)
	{
		UnloadComponent();
		return false;
	}

	IImportManager* pImportManager = (*pfnCreateImportManager)();
	if (!pImportManager)
	{
		UnloadComponent();
		return false;
	} else
		(*pfnReleaseImportManager)(pImportManager);

	bIsInitialized = true;
	return bIsInitialized;
}

bool CImportManagerComponent::UnloadComponent()
{
	bool bRet = true;
	bIsInitialized = false;

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
		hLibrary = NULL;
	}
	
	return bRet;
}

bool CImportManagerComponent::VerifyWhetherExists()
{
	// Tis method is not implemented because you can locate BuilderElements.dll and 
	//  NetworkImport.dll in folder that differs from your application default folder.    
	// You must make them accessible for LoadLibrary call.
	
	return true;
}

CString CImportManagerComponent::GetComponentName()
{
	CString csComponentName = _T("");
	if (bIsInitialized && pfnGetComponentName)
	{		
		csComponentName = (*pfnGetComponentName)();
	} 
	return csComponentName;	
}

CString CImportManagerComponent::GetComponentVersion()
{
	CString csComponentVirsion = _T("");
	if (bIsInitialized && pfnGetComponentVersion)
	{		
		csComponentVirsion = (*pfnGetComponentVersion)();
	} 
	return csComponentVirsion;
}

// IObject declarations section	
CString CImportManagerComponent::GetClassString()
{
	return _T("CImportManagerComponent");
}

void CImportManagerComponent::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch (iIDD)
	{
	case IDD_IComponent:
		*ppvObject = (IComponent*)this;
		break;
	}
}
