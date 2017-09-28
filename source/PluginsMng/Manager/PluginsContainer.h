#pragma once

#include "ContainerCore.h"
#include "PluginInstance.h"

#include "Templates\Enumerator.h"

class CPluginsContainer : public IPluginsContainer
{
public:
	CPluginsContainer(void);
	~CPluginsContainer(void);

// IPluginsContainer declarations section
public:
	virtual void			LoadInstalledPlugins(CString& csAppFolder);
	virtual void			RefreshPluginsList(CString& csAppFolder);
	virtual void			ReleaseInstalledPlugins();

	virtual void			GetWrongFilesList(CList<CString, CString>* pList);

	virtual void			SetAppController(IAppController* pController);

	ENUMERATOR(mPluginsList, CPluginInstance*, CreateEnumerator, GetNextPlugin, posPluginsEnum)

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void ** ppvObject);

private:
	void					AddPlugin(CString& csPluginFilePath, CString& csPluginFileName);

	CList<CPluginInstance*, CPluginInstance*>		mPluginsList;
	CList<CString, CString>							mWrongFiles;

	IAppController*			pAppController;
};
