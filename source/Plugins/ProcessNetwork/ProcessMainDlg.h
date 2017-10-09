#pragma once

#include "CmnApp.h"

#include "Resource.h"
#include "afxcmn.h"

// CProcessMainDlg dialog
#include "ProcessNetworkDlg.h"
#include "ProcessVisualDlg.h"
#include "ProcessSignalsDlg.h"

class CProcessMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessMainDlg)

public:
	CProcessMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessMainDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_MAIN };

	CProcessNetworkDlg	mProcessNetworkDlg;
	CProcessVisualDlg	mProcessVisualDlg;
	CProcessSignalsDlg	mProcessSignalsDlg;
	CDialog*			pOnTop;


	void			SetAppController(IAppController* pController);

private:
	IAppController* pAppController;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl mMainTab;
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
};
