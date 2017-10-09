#pragma once


// CParamsDlg dialog

#include "Resource.h"
#include "afxwin.h"

#include "../Trainer/BackProp.h"

class CParamsDlg : public CDialog
{
	DECLARE_DYNAMIC(CParamsDlg)

	// Dialog Data
	enum { IDD = IDD_PARAMS_DLG };

public:
	CParamsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CParamsDlg();

	sBPSettings* pSettings_;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	float fromValue_;
	float toValue_;
	float constValue_;
	CComboBox trainingMethod_;
	float hiddenSpeed_;
	float mse_;
	int loops_;
	CComboBox approach_;
	CComboBox hiddenActivation_;
	CComboBox outputActivation_;

public:
	afx_msg void OnBnClickedRandomValues();
	afx_msg void OnBnClickedConstantValue();
	afx_msg void OnBnClickedAdoptiveMethod();
	afx_msg void OnBnClickedNoInitWeights();

	afx_msg void OnBnClickedShowFannAbout();

private:
	
	void SetupWeightsInit(int method);
	//void EnableWeightsSection(BOOL enable);
	int GetWeightsInitMethod();
	void SelectActivation(CComboBox& combo, unsigned int function);
	unsigned int GetActivation(CComboBox& combo);

};
