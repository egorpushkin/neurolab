#pragma once
#include "afxcmn.h"


// CPluginPropertiesDlg dialog
#include "..\Manager\ContainerCore.h"

#include "CommonPluginPropDlg.h"

class CPluginPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CPluginPropertiesDlg)

public:
	CPluginPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPluginPropertiesDlg();
    
// Dialog Data
	enum { IDD = IDD_PLUGIN_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mPropTab;
	virtual BOOL OnInitDialog();

	void			SetPluginInstance(CPluginInstance* pInstance);

	CDialog*				mOnTop;
	CCommonPluginPropDlg	mCommonPropDlg;

private:
	CPluginInstance* pPluginInstance;

	CDialog*		pPluginPropPage;

	bool			bIsInited;
public:
	afx_msg void OnPaint();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnTcnSelchangePluginPropertiesTab(NMHDR *pNMHDR, LRESULT *pResult);
};
