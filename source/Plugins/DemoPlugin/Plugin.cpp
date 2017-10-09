#include "StdAfx.h"
#include ".\plugin.h"

#include "interface_idds.h"
#include "CmnFactory.h"
#include "CmnOutput.h"

CPlugin::CPlugin(void)
{
}

CPlugin::~CPlugin(void)
{
}

// IPluginControl implementations section
void CPlugin::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

void CPlugin::StartPlugin()
{
	AfxMessageBox("Plugin start code.");
}

// IObject implementations section
CString	CPlugin::GetClassString()
{
	return _T("CPlugin");
}

void CPlugin::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IPluginControl:
		*ppvObject = (IPluginControl*)this;
		break;
	case IDD_IPluginBarControl:
		mPluginBar.QueryInterface(iIDD, ppvObject);
		break;	
	case IDD_IPluginPropertiesControl:
		mPluginPropPage.QueryInterface(iIDD, ppvObject);
		break;	
	}
}