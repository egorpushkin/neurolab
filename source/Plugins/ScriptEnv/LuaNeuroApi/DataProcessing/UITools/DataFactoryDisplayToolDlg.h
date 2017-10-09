#pragma once

#include "..\..\..\Resource.h"
// CDataFactoryDisplayToolDlg dialog

#include "CmnDataFactory.h"
#include "afxwin.h"

struct sDataFactoryDisplayStruct
{
	int				iWidth;
	int				iHeight;

	CString			csName;

    CDataFactory	mDataFactory;
};

class CDataFactoryDisplayToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataFactoryDisplayToolDlg)

public:
	CDataFactoryDisplayToolDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataFactoryDisplayToolDlg();

// Dialog Data
	enum { IDD = IDD_SCR_DATAPROC_DISPLAY_FACTORY };

	sDataFactoryDisplayStruct*	pData;

	CDataImageCtrl				mDataImageCtrl;

	bool						bAlwaysOnTop;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton mDataPropCtrl;
	afx_msg void OnBnClickedControlProperties();
	afx_msg void OnBnClickedDataFactorySaveAs();
	CButton mCtrlDFSaveAs;
	afx_msg void OnBnClickedDfTlAlwaysOnTop();
	CButton mAlwaysOnTop;
	void UpdateAlwaysOnTopButton();
};
