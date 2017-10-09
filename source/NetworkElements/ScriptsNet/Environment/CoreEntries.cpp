#include "StdAfx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "..\Manager\ScriptsNetManager.h"

IExternalElementsContainer* CreateExternalManager()
{
	CScriptsNetManager* pScriptsNetManager = new CScriptsNetManager;

	IExternalElementsContainer* pContainer = NULL;
	pScriptsNetManager->QueryInterface(IDD_IExternalManager, (void**)&pContainer);
	
	return pContainer;

}

void ReleaseExternalManager(IExternalElementsContainer* pContainer)
{
	if (pContainer)
		delete pContainer;
}