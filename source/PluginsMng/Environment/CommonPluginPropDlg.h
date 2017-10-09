#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCommonPluginPropDlg dialog

#include "..\Manager\ContainerCore.h"

class CCommonPluginPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommonPluginPropDlg)

public:
	CCommonPluginPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommonPluginPropDlg();

// Dialog Data
	enum { IDD = IDD_COMMON_PLUGIN_PROPERTIES_DLG };

	void UpdatePropertyPage(CPluginInstance* pInstance);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mPluginName;
	CString mPluginVersion;
	CString mBarPresenceString;
	CString mPluginFileName;
	CString mLibraryType;
	CString mLibraryVersion;
	CString mLastModified;
	CString mFileSize;
	CListCtrl mSymbolsList;
	CListCtrl mInterfacesTable;
	virtual BOOL Create(int iIDD, CWnd* pParentWnd = NULL);
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	CString mInstanceAddress;
};
