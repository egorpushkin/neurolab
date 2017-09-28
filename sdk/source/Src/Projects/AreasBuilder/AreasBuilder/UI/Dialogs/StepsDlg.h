#pragma once

#include "../Controls/BrowserControl.h"

// CStepsDlg dialog

class CStepsDlg : public CDialog
{
	DECLARE_DYNAMIC(CStepsDlg)

public:
	CStepsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStepsDlg();

// Dialog Data
	enum { IDD = IDD_STEPS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	BrowserControl		browserControl_;

	CString				appFolder_;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(UINT resourceId, CWnd* pParentWnd = NULL);
};
