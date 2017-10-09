#pragma once


// CPluginBar dialog

#include "Resource.h"

#include "CmnPlugin.h"

class CPluginBar : public CDialog, public IPluginBarControl
{
	DECLARE_DYNAMIC(CPluginBar)

public:
	CPluginBar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPluginBar();

// Dialog Data
	enum { IDD = IDD_PLUGIN_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// IPluginBarControl declarations section
public:
	virtual bool			IsBarCreated();
	virtual void			SetBarState(bool bState);

	virtual CDialog*		GetBarDialog();
	virtual int				GetBarIDD();

	virtual CString			GetBarTitle();

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	bool					bIsBarCreated;
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
