#include "stdafx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "Plugin.h"

IPluginControl*	CreatePluginInstance()
{
	CPlugin* pPlugin = new CPlugin;

	IPluginControl* pPluginControl = NULL;
	pPlugin->QueryInterface(IDD_IPluginControl, (void**)&pPluginControl);
	
	return pPluginControl;
}

void ReleasePluginInstance(IPluginControl* pPlugin)
{
	if (pPlugin)
		delete pPlugin;
}

void GetPluginInfo(PLUGIN_INFO* pInfoStruct)
{
	if (!pInfoStruct)
		return;

	pInfoStruct->csLibraryType = _T("NeuroLab.Plugin");
	pInfoStruct->csLibraryVersion = _T("1.0.0.0b");

	pInfoStruct->csName = _T("Scripting Environment");
	pInfoStruct->csVersion = _T("1.0.0.0a");
	pInfoStruct->bHasBar = false;
	pInfoStruct->bHasPropertiesPage = false;	
}