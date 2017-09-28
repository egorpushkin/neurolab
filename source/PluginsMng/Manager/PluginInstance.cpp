#include "StdAfx.h"
#include ".\plugininstance.h"

#include "System\Directory.h"

CPluginInstance::CPluginInstance(CString& FileName)
{
	csPluginFileName = FileName;

	hLibrary = NULL;

	pfnCreatePluginInstance = NULL;
	pfnReleasePluginInstance = NULL;

	pfnGetPluginInfo = NULL;

	pPluginControl = NULL;

	IsPropertiesDlgActivated = false;
}

CPluginInstance::~CPluginInstance(void)
{
	ReleasePluginInstance();
}

bool CPluginInstance::CreatePluginInstance()
{
	bool bRet = true;

/*	CString tmLibFileName = CPath::GetFileName(csPluginFileName);
	if (tmLibFileName != _T("HopfieldLearning.dll") && 
		tmLibFileName != _T("ProcessNetwork.dll") && 
		tmLibFileName != _T("ScriptEnv.dll") && 
		tmLibFileName != _T("StatVerifier.dll"))
		return false; */

	hLibrary = LoadLibrary(csPluginFileName);
	if (!hLibrary)
		return false;

	(FARPROC &)pfnCreatePluginInstance = GetProcAddress(hLibrary, "CreatePluginInstance");
	if (!pfnCreatePluginInstance)
	{
		ReleasePluginInstance();
		return false;
	}
	
	(FARPROC &)pfnReleasePluginInstance = GetProcAddress(hLibrary, "ReleasePluginInstance");
	if (!pfnReleasePluginInstance)
	{
		ReleasePluginInstance();
		return false;
	}

	(FARPROC &)pfnGetPluginInfo = GetProcAddress(hLibrary, "GetPluginInfo");
	if (!pfnGetPluginInfo)
	{
		ReleasePluginInstance();
		return false;
	}

	(*pfnGetPluginInfo)(&mPluginInfo);
	if (mPluginInfo.csLibraryType != _T("NeuroLab.Plugin"))
	{
		ReleasePluginInstance();
		return false;		
	}

	pPluginControl = (*pfnCreatePluginInstance)();

	return bRet;
}

void CPluginInstance::ReleasePluginInstance()
{
	if (pPluginControl)
	{
		(*pfnReleasePluginInstance)(pPluginControl);
		pPluginControl = NULL;
	}

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
		hLibrary = NULL;
	}
}