#pragma once

#include "CmnElement.h"
#include "CmnFFTProcessor.h"

// CFFTProcessorPropertiesDlg dialog

class CFFTProcessorPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CFFTProcessorPropertiesDlg)

public:
	CFFTProcessorPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFFTProcessorPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_FFT_PROCESSOR_PROPERTIES_DLG };

	IFFTProcessorControl*		pFFTProcessorControl;
	ILayerControl*				pLayerControl;

	void						UpdateElementProperties();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mSamplesCount;
	BOOL mNormalizeSpectr;
	int mInputsCount;
	int mLayerDimension;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnEnChangeSamplesCount();
	afx_msg void OnBnClickedComplexInputData();
	afx_msg void OnBnClickedRealInputData();
};
