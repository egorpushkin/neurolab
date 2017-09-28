#include "StdAfx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "..\Manager\PackageManager.h"

IExternalElementsContainer* CreateExternalManager()
{
	CPackageManager* pPackageManager = new CPackageManager;

	IExternalElementsContainer* pContainer = NULL;
	pPackageManager->QueryInterface(IDD_IExternalManager, (void**)&pContainer);
	
	return pContainer;

}

void ReleaseExternalManager(IExternalElementsContainer* pContainer)
{
	if (pContainer)
		delete pContainer;
}