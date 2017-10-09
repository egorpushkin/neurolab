#pragma once

// CVerificationSettingsDlg dialog

#include "VerificationDlg.h"

class CVerificationSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CVerificationSettingsDlg)

public:
	CVerificationSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVerificationSettingsDlg();

// Dialog Data
	enum { IDD = IDD_VERIFICATION_SETTINGS_DLG };

	sVerificationSettings*	pSettings;

	void				EnableMaxError(BOOL bEnable);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	
	float mMaxError;
	int mVerifMode;


	afx_msg void OnBnClickedConditionEqual();
	afx_msg void OnBnClickedConditionCoinside();
	afx_msg void OnBnClickedConditionError();
};
