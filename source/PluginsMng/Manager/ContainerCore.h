#pragma once 

#include "Templates\Enumerator.h"
#include "PluginInstance.h"

#include "CmnObjects.h"

interface IPluginsContainer : public IObject
{
	virtual void			LoadInstalledPlugins(CString& csAppFolder) = 0;
	virtual void			RefreshPluginsList(CString& csAppFolder) = 0;
	virtual void			ReleaseInstalledPlugins() = 0;

	virtual void			GetWrongFilesList(CList<CString, CString>* pList) = 0;

	virtual void			SetAppController(IAppController* pController) = 0;

	INTERFACE_ENUMERATOR_DECLARATION(CPluginInstance*, CreateEnumerator, GetNextPlugin)
};