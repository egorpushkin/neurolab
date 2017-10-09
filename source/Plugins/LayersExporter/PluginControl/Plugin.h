#pragma once

#include "CmnPlugin.h"
#include "CmnApp.h"

class CPlugin : public IPluginControl
{
public:
	CPlugin(void);
	~CPlugin(void);

// IPluginControl declarations section
public:
	virtual void			SetAppController(IAppController* pController);
	virtual void			StartPlugin();	

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	IAppController*			pAppController;
};
