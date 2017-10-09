#pragma once


// CPluginPropertiesPage dialog
#include "CmnPlugin.h"

#include "Resource.h"

class CPluginPropertiesPage : public CDialog, public IPluginPropertiesControl
{
	DECLARE_DYNAMIC(CPluginPropertiesPage)

public:
	CPluginPropertiesPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPluginPropertiesPage();

// Dialog Data
	enum { IDD = IDD_PLUGIN_PROPERTIES_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// IPluginPropertiesControl declarations section
	virtual CDialog*		GetPropertyDialog();
	virtual int				GetDialogIDD();

	virtual CString			GetPropertyPageTitle();

	virtual void			ProcessUpdateProperties();

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);
};
