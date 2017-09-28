// DataCreatorDlg.h : header file
//

#pragma once

#include "UIControls\InfoBar.h"
#include "afxcmn.h"

#include "DataFilesDlg.h"
#include "DataCollectionsDlg.h"
#include "ConvertingProjectDlg.h"

// CDataCreatorDlg dialog
class CDataCreatorDlg : public CDialog
{
// Construction
public:
	CDataCreatorDlg(CWnd* pParent = NULL);	// standard constructor

	CInfoBar			mTitleBar;

// Dialog Data
	enum { IDD = IDD_DATACREATOR_DIALOG };

	void				ShowUserGuide();
	void				ShowSDKDocumentation();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CDialog*			pOnTop;
	CDataFilesDlg		mDataFilesDlg;
	CDataCollectionsDlg	mDataCollectionsDlg;
	CConvertingProjectDlg mConvertingProjectDlg;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mMainTab;
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
};
