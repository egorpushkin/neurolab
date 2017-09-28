// FFTProcessorPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\..\SignalProcessors.h"
#include "FFTProcessorPropertiesDlg.h"
#include ".\fftprocessorpropertiesdlg.h"

// CFFTProcessorPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CFFTProcessorPropertiesDlg, CDialog)
CFFTProcessorPropertiesDlg::CFFTProcessorPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFFTProcessorPropertiesDlg::IDD, pParent)
	, mSamplesCount(0)
	, mNormalizeSpectr(FALSE)
	, mInputsCount(0)
	, mLayerDimension(0)
	, pFFTProcessorControl(NULL)
	, pLayerControl(NULL)
{
}

CFFTProcessorPropertiesDlg::~CFFTProcessorPropertiesDlg()
{
}

void CFFTProcessorPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SAMPLES_COUNT, mSamplesCount);
	DDX_Check(pDX, IDC_NORMALIZE_SPECTR, mNormalizeSpectr);
	DDX_Text(pDX, IDC_INPUTS_COUNT, mInputsCount);
	DDX_Text(pDX, IDC_LAYER_DIMENSION, mLayerDimension);
}


BEGIN_MESSAGE_MAP(CFFTProcessorPropertiesDlg, CDialog)
	ON_EN_CHANGE(IDC_SAMPLES_COUNT, OnEnChangeSamplesCount)
	ON_BN_CLICKED(IDC_COMPLEX_INPUT_DATA, OnBnClickedComplexInputData)
	ON_BN_CLICKED(IDC_REAL_INPUT_DATA, OnBnClickedRealInputData)
END_MESSAGE_MAP()


// CFFTProcessorPropertiesDlg message handlers

BOOL CFFTProcessorPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pFFTProcessorControl != NULL);
	ASSERT(pLayerControl != NULL);

    mSamplesCount = pLayerControl->GetInputsCount();
	mNormalizeSpectr = pFFTProcessorControl->GetNormalizationMethod();
	    
	if (pFFTProcessorControl->GetTransformDirection() == FFTPC_DIRECT_TRANSFORM)
		((CButton*)GetDlgItem(IDC_DIRECT_TRANSFORM))->SetCheck(BST_CHECKED);
	else
		((CButton*)GetDlgItem(IDC_INVERSE_TRANSFORM))->SetCheck(BST_CHECKED);

	if (pFFTProcessorControl->GetFFTDataModel() == FFTPC_COMPLEX_DATA)
	{
		((CButton*)GetDlgItem(IDC_COMPLEX_INPUT_DATA))->SetCheck(BST_CHECKED);
		mSamplesCount /= 2;
	}
	else
		((CButton*)GetDlgItem(IDC_REAL_INPUT_DATA))->SetCheck(BST_CHECKED);

	UpdateData(FALSE);

	UpdateElementProperties();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFFTProcessorPropertiesDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateElementProperties();

	UpdateData(TRUE);

	if (mSamplesCount <= 0)
	{
		AfxMessageBox(_T("You must enter valid number of samples."));
		return;
	}

	int iValue = mInputsCount;
	bool bIsPower2 = true;
	while (iValue >= 2)
	{
		int iRemainder = iValue % 2;
		if (iRemainder != 0)
		{
			bIsPower2 = false;
			break;			
		}
		iValue /= 2;
	}
	if (!bIsPower2)
	{
		AfxMessageBox(_T("You must enter valid number of samples."));
		return;
	}

	pLayerControl->CreateWeights(mInputsCount, mLayerDimension);
	pFFTProcessorControl->SetNormalizationMethod(mNormalizeSpectr);

	if (((CButton*)GetDlgItem(IDC_COMPLEX_INPUT_DATA))->GetCheck() == BST_CHECKED)
		pFFTProcessorControl->SetFFTDataModel(FFTPC_COMPLEX_DATA);
	else
		pFFTProcessorControl->SetFFTDataModel(FFTPC_REAL_DATA);

	if (((CButton*)GetDlgItem(IDC_DIRECT_TRANSFORM))->GetCheck() == BST_CHECKED)
		pFFTProcessorControl->SetTransformDirection(FFTPC_DIRECT_TRANSFORM);
	else
		pFFTProcessorControl->SetTransformDirection(FFTPC_INVERSE_TRANSFORM);

	CDialog::OnOK();
}

void CFFTProcessorPropertiesDlg::UpdateElementProperties()
{
	UpdateData(TRUE);
	
	mInputsCount = mSamplesCount;
	mLayerDimension = mSamplesCount;
	
	if (((CButton*)GetDlgItem(IDC_COMPLEX_INPUT_DATA))->GetCheck() == BST_CHECKED)
	{
		mInputsCount *= 2;
		mLayerDimension *= 2;
	}

	UpdateData(FALSE);
}
void CFFTProcessorPropertiesDlg::OnEnChangeSamplesCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateElementProperties();
}

void CFFTProcessorPropertiesDlg::OnBnClickedComplexInputData()
{
	// TODO: Add your control notification handler code here
	UpdateElementProperties();
}

void CFFTProcessorPropertiesDlg::OnBnClickedRealInputData()
{
	// TODO: Add your control notification handler code here
	UpdateElementProperties();
}
