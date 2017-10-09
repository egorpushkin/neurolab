// CannyDetectorParametersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\..\EdgeDetectors.h"
#include "CannyDetectorParametersDlg.h"
#include ".\cannydetectorparametersdlg.h"


// CCannyDetectorParametersDlg dialog

IMPLEMENT_DYNAMIC(CCannyDetectorParametersDlg, CDialog)
CCannyDetectorParametersDlg::CCannyDetectorParametersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCannyDetectorParametersDlg::IDD, pParent)
	, mSigmaX(0)
	, mSigmaY(0)
	, mCannyFraction(0)
	, mLowThreshold(0)
	, mHighThreshold(0)
	, mMinSegmentLength(0)
	, mMaxDeviation(0)
{
}

CCannyDetectorParametersDlg::~CCannyDetectorParametersDlg()
{
}

void CCannyDetectorParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SIGMA_X, mSigmaX);
	DDX_Text(pDX, IDC_SIGMA_Y, mSigmaY);
	DDX_Text(pDX, IDC_CANNY_FRACTION, mCannyFraction);
	DDX_Text(pDX, IDC_LOW_THRESHOLD, mLowThreshold);
	DDX_Text(pDX, IDC_HIGH_THRESHOLD, mHighThreshold);
	DDX_Text(pDX, IDC_MIN_SEGMENT_LENGTH, mMinSegmentLength);
	DDX_Text(pDX, IDC_MAX_DEVIATION, mMaxDeviation);
}


BEGIN_MESSAGE_MAP(CCannyDetectorParametersDlg, CDialog)
	ON_BN_CLICKED(IDC_RESTORE_DEFAULTS, OnBnClickedRestoreDefaults)
END_MESSAGE_MAP()


// CCannyDetectorParametersDlg message handlers

#define alert_wrong_input(text)								\
	{														\
		AfxMessageBox(text);								\
		return;												\
	}

void CCannyDetectorParametersDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mSigmaX <= 0 || mSigmaY <= 0)
		alert_wrong_input(_T("You must enter valid Gaussian sigma values for both dimensions."))	
	
	if (mCannyFraction <= 0)
		alert_wrong_input(_T("You must enter valid Canny fraction value."))	

	if (mLowThreshold <= 0)
		alert_wrong_input(_T("You must enter valid Canny low threshold value."))	

	if (mHighThreshold <= 0)
		alert_wrong_input(_T("You must enter valid Canny high threshold value."))	

	if (mMinSegmentLength <= 0)
		alert_wrong_input(_T("You must enter valid minimum length of segment in polygonal approximation."))	

	if (mMaxDeviation <= 0)
		alert_wrong_input(_T("You must enter valid maximum deviation in polygonal approximation."))	

	CDialog::OnOK();
}

void CCannyDetectorParametersDlg::OnBnClickedRestoreDefaults()
{
	// TODO: Add your control notification handler code here
	mSigmaX = 3.0f;
	mSigmaY = 3.0f;
	mCannyFraction = 0.3f;
	mLowThreshold = 2.0f;
	mHighThreshold = 4.0f;
	mMinSegmentLength = 5.0f;
	mMaxDeviation = 1.5f;

	UpdateData(FALSE);
}
