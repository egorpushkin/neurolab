#pragma once

#include "CmnPlugin.h"

typedef IPluginControl* (*PCREATE_PLUGIN_INSTANCE_ROUTINE)();
typedef void (*PRELEASE_PLUGIN_INSTANCE_ROUTINE)(IPluginControl* pPlugin);

typedef void (*PGET_PLUGIN_INFO_ROUTINE)(PLUGIN_INFO* pInfoStruct);

class CPluginInstance
{
public:
	CPluginInstance(CString& FileName);
	~CPluginInstance(void);

	bool			CreatePluginInstance();
	void			ReleasePluginInstance();

	PLUGIN_INFO		mPluginInfo;

	CString			csPluginFileName;

	IPluginControl*						pPluginControl;

	bool			IsPropertiesDlgActivated;

private:
	HMODULE			hLibrary;

	PCREATE_PLUGIN_INSTANCE_ROUTINE		pfnCreatePluginInstance;
	PRELEASE_PLUGIN_INSTANCE_ROUTINE	pfnReleasePluginInstance;

	PGET_PLUGIN_INFO_ROUTINE			pfnGetPluginInfo;
};
