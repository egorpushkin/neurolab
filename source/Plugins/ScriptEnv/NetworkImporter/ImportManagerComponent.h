//	This code is a part of Network Importing SDK.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ImportManagerComponent.h
//	Description: Import manager component.

#pragma once

// Network Importing SDK header
#include "CmnNetworkImport.h"
#include "CmnComponent.h"

typedef IImportManager* (*PCREATE_IMPORT_MANAGER_ROUTINE)(void);
typedef void (*PRELEASE_IMPORT_MANAGER_ROUTINE)(IImportManager* pManager);

// CImportManagerComponent implementation
class CImportManagerComponent : public IComponent
{
public:
	CImportManagerComponent();
	~CImportManagerComponent();

    IImportManager*			GetImportManager();
	void					ReleaseImportManager(IImportManager* pManager);

	bool					IsLoaded();

	CString					GetAppFolder();

// IComponent declarations section	
	virtual bool			LoadComponent();
	virtual bool			UnloadComponent();
	virtual bool			VerifyWhetherExists();

	virtual CString			GetComponentName();
	virtual CString			GetComponentVersion();
	
// IObject declarations section	
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	bool					bIsInitialized;

	CString					csNetworkImportLib;
	CString					csAppFolder;

	HMODULE					hLibrary;

	PGET_COMPONENT_NAME_ROUTINE			pfnGetComponentName;
	PGET_COMPONENT_VERSION_ROUTINE		pfnGetComponentVersion;

	PCREATE_IMPORT_MANAGER_ROUTINE		pfnCreateImportManager;
	PRELEASE_IMPORT_MANAGER_ROUTINE		pfnReleaseImportManager;
};