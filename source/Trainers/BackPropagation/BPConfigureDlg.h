#pragma once


// CBPConfigureDlg dialog
#include "Resource.h"

#include "BackProp.h"
#include "afxwin.h"
// CBPConfigureDlg dialog

class CBPConfigureDlg : public CDialog
{
	DECLARE_DYNAMIC(CBPConfigureDlg)

public:
	CBPConfigureDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBPConfigureDlg();

	sBPSettings*			pSettings;

	void					EnableInitSection(BOOL bEnable);

// Dialog Data
	enum { IDD = IDD_BP_CONFIGURE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	float fOutputSpeed;
	float fHiddenSpeed;
	float fOutputChange;
	float fHiddenChange;
	float fMaxError;
	int iLoopsCount;
	bool bOutputIncrement;
	bool bHiddenIncrement;

	bool bOutputChangeState;
	bool bHiddenChangeState;

	BOOL mSelectRandowSymbolForTraining;

	BOOL mSaveNeuronWeights;

	BOOL mInitializeWeights;
	CEdit mStartValueCtrl;
	CEdit mEndValueCtrl;
	CEdit mConstantValueCtrl;
	float mStartValue;
	float mEndValue;
	float mConstantValue;

	CStatic mInitStaticTo;

	bool bUseRandomIntialization; 

protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOutputIncrement();
	afx_msg void OnBnClickedHiddenIncrement();
	afx_msg void OnBnClickedOutputMultiplier();
	afx_msg void OnBnClickedHiddenMultiplier();
	afx_msg void OnBnClickedInitializeWeights();
	afx_msg void OnBnClickedRandomValues();
	afx_msg void OnBnClickedConstantValue();
};
