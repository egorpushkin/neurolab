#pragma once

#include "CmnObjects.h"
#include "CmnApp.h"

struct PLUGIN_INFO
{
	CString			csLibraryType;
	CString			csLibraryVersion;
	CString			csName;
	CString			csVersion;
	bool			bHasBar;
	bool			bHasPropertiesPage;
};

interface IPluginControl : public IObject
{
	virtual void			SetAppController(IAppController* pController) = 0;
	
	virtual void			StartPlugin() = 0;	
	

};


interface IPluginBarControl : public IObject
{
	virtual bool			IsBarCreated() = 0;
	virtual void			SetBarState(bool bState) = 0;

	virtual CDialog*		GetBarDialog() = 0;
	virtual int				GetBarIDD() = 0;

	virtual CString			GetBarTitle() = 0;




};

interface IPluginPropertiesControl : public IObject
{
	virtual CDialog*		GetPropertyDialog() = 0;
	virtual int				GetDialogIDD() = 0;

	virtual CString			GetPropertyPageTitle() = 0;

	virtual void			ProcessUpdateProperties() = 0;


};