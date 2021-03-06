#pragma once


// CCannyDetectorParametersDlg dialog

class CCannyDetectorParametersDlg : public CDialog
{
	DECLARE_DYNAMIC(CCannyDetectorParametersDlg)

public:
	CCannyDetectorParametersDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCannyDetectorParametersDlg();

// Dialog Data
	enum { IDD = IDD_CANNY_DETECTOR_PARAMETERS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float mSigmaX;
	float mSigmaY;
	float mCannyFraction;
	float mLowThreshold;
	float mHighThreshold;
	float mMinSegmentLength;
	float mMaxDeviation;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedRestoreDefaults();
};
