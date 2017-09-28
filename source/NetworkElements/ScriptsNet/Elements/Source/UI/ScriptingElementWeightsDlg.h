#pragma once

#include "CmnElement.h"

// CScriptingElementWeightsDlg dialog

class CScriptingElementWeightsDlg : public CDialog
{
	DECLARE_DYNAMIC(CScriptingElementWeightsDlg)

public:
	CScriptingElementWeightsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptingElementWeightsDlg();

// Dialog Data
	enum { IDD = IDD_SCREL_WEIGHTS_DLG };

	void			EnableWeightsInfo(BOOL bEnable);

	void			SetElement(IElement* Element);

private:
	IElement*		pElement;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int mInputsCount;
	int mLayerDimension;
	afx_msg void OnBnClickedDonotStoreWeights();
	afx_msg void OnBnClickedStoreWeights();
protected:
	virtual void OnOK();
};
