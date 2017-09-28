#include "StdAfx.h"
#include "ExternalManagerInstance.h"

CExternalManagerInstance::CExternalManagerInstance()
	: csFilePath(_T(""))
	, hLibrary(NULL)
	, pfnCreateExternalManager(NULL)
	, pfnReleaseExternalManager(NULL)
	, pContainer(NULL)
{
}

CExternalManagerInstance::~CExternalManagerInstance()
{
	ReleaseExternalManager();
}

bool CExternalManagerInstance::LoadExternalManager(CString& LibraryPath)
{
	hLibrary = LoadLibrary(LibraryPath);
	if (!hLibrary)
		return false;	

	(FARPROC &)pfnCreateExternalManager = GetProcAddress(hLibrary, "CreateExternalManager");
	if (!pfnCreateExternalManager)
	{
		ReleaseExternalManager();
		return false;
	}

	(FARPROC &)pfnReleaseExternalManager = GetProcAddress(hLibrary, "ReleaseExternalManager");
	if (!pfnReleaseExternalManager)
	{
		ReleaseExternalManager();
		return false;
	}

	pContainer = (*pfnCreateExternalManager)();
	if (!pContainer)
	{
		ReleaseExternalManager();
		return false;
	}

	csFilePath = LibraryPath;

	return true;
}

void CExternalManagerInstance::ReleaseExternalManager()
{
	if (pContainer && pfnReleaseExternalManager)
		(*pfnReleaseExternalManager)(pContainer);
		
	pContainer = NULL;

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
		hLibrary = NULL;
	}

	pfnCreateExternalManager = NULL;
	pfnReleaseExternalManager = NULL;
}

IExternalElementsContainer* CExternalManagerInstance::GetContainer()
{
	return pContainer;
}