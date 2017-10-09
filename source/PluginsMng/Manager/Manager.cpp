#include "StdAfx.h"
#include ".\manager.h"

#include "interface_idds.h"

CManager::CManager(void)
{
	pAppController = NULL;
}

CManager::~CManager(void)
{
}

// IManagerControl implementations section
BOOL CManager::InitializeManagerInstance()
{
	mPluginsContainer.LoadInstalledPlugins(csAppFolder);

	IPluginsContainer* pContainer;
	QueryInterface(IDD_IPluginsContainer, (void**)&pContainer);
	mPluginsPanelDlg.SetPluginsContainer(pContainer);
	
	return TRUE;
}

BOOL CManager::ReleaseManagerInstance()
{
	mPluginsContainer.ReleaseInstalledPlugins();
	
	return TRUE;
}

void CManager::SetAppFolder(CString& csFolder)
{
	csAppFolder = csFolder;
	mPluginsPanelDlg.SetAppFolder(csFolder);
}

void CManager::SetAppController(IAppController* pController)
{
	pAppController = pController;
	mPluginsPanelDlg.SetAppController(pAppController);
	mPluginsContainer.SetAppController(pAppController);
}

// IObject implementations section
CString	CManager::GetClassString()
{
	return CString("CManager");
}

void CManager::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IManagerControl:
		*ppvObject = (IManagerControl*)this;
		break;
	case IDD_IPluginsPanelControl:
		mPluginsPanelDlg.QueryInterface(iIDD, ppvObject);
		break;
	case IDD_IPluginsContainer:
		mPluginsContainer.QueryInterface(iIDD, ppvObject);
		break;
	}
}
