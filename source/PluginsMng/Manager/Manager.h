#pragma once

#include "CmnManager.h"

#include "..\Environment\PluginsPanelDlg.h"
#include "PluginsContainer.h"

class CManager : public IManagerControl
{
public:
	CManager(void);
	~CManager(void);

// IManagerControl declarations section
public:
	virtual BOOL			InitializeManagerInstance();
	virtual BOOL			ReleaseManagerInstance();
	virtual void			SetAppFolder(CString& csFolder);

	virtual void			SetAppController(IAppController* pController);

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CString					csAppFolder;
	
	IAppController*			pAppController;

// Plugins Panel
	CPluginsPanelDlg		mPluginsPanelDlg;

// Plugins Container 
	CPluginsContainer		mPluginsContainer;
};
