#pragma once

#include "CmnExternalElement.h"

typedef IExternalElementsContainer* (*PCREATE_EXTERNAL_CONTAINER_ROUTINE)();
typedef void (*PRELEASE_EXTERNAL_CONTAINER_ROUTINE)(IExternalElementsContainer* pContainer);

class CExternalManagerInstance
{
public:
	CExternalManagerInstance();
	~CExternalManagerInstance();

	bool			LoadExternalManager(CString& LibraryPath);
	void			ReleaseExternalManager();
	
	IExternalElementsContainer*		GetContainer();

private:
	CString			csFilePath;

	HMODULE			hLibrary;

	PCREATE_EXTERNAL_CONTAINER_ROUTINE	pfnCreateExternalManager;
	PRELEASE_EXTERNAL_CONTAINER_ROUTINE	pfnReleaseExternalManager;

	IExternalElementsContainer*		pContainer;
};
