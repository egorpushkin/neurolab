#pragma once

#include "KohonenTrainer.h"
// CKohonenPropDlg dialog

class CKohonenPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CKohonenPropDlg)

public:
	CKohonenPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKohonenPropDlg();

// Dialog Data
	enum { IDD = IDD_KOHONEN_PROP_DLG };

	sSettings* pSettings;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL mNormalizeInputs;
	BOOL mInitializeWeights;
	afx_msg void OnBnClickedInitializeWeights();
	float mFromValue;
	float mToValue;
	float mMaxDistance;
	int mLoopsCount;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	float mStartSpeed;
	float mMultiplier;
	BOOL mNormilizeWeights;
};
