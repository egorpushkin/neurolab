// KohonenPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KohonenTraining.h"
#include "KohonenPropDlg.h"
#include ".\kohonenpropdlg.h"


// CKohonenPropDlg dialog

IMPLEMENT_DYNAMIC(CKohonenPropDlg, CDialog)
CKohonenPropDlg::CKohonenPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKohonenPropDlg::IDD, pParent)
	, mNormalizeInputs(FALSE)
	, mInitializeWeights(FALSE)
	, mFromValue(0)
	, mToValue(0)
	, mMaxDistance(0)
	, mLoopsCount(0)
	, mStartSpeed(0)
	, mMultiplier(0)
	, mNormilizeWeights(FALSE)
{
}

CKohonenPropDlg::~CKohonenPropDlg()
{
}

void CKohonenPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_NORMALIZE_INPUT_SYMBOLS, mNormalizeInputs);
	DDX_Check(pDX, IDC_INITIALIZE_WEIGHTS, mInitializeWeights);
	DDX_Text(pDX, IDC_FROM_VALUE, mFromValue);
	DDX_Text(pDX, IDC_TO_VALUE, mToValue);
	DDX_Text(pDX, IDC_MAXIMUM_DISTANCE, mMaxDistance);
	DDX_Text(pDX, IDC_LOOPS_COUNT, mLoopsCount);
	DDX_Text(pDX, IDC_EDIT1, mStartSpeed);
	DDX_Text(pDX, IDC_EDIT2, mMultiplier);
	DDX_Check(pDX, IDC_CHECK2, mNormilizeWeights);
}


BEGIN_MESSAGE_MAP(CKohonenPropDlg, CDialog)
	ON_BN_CLICKED(IDC_INITIALIZE_WEIGHTS, OnBnClickedInitializeWeights)
END_MESSAGE_MAP()


// CKohonenPropDlg message handlers

void CKohonenPropDlg::OnBnClickedInitializeWeights()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetDlgItem(IDC_FROM_VALUE)->EnableWindow(mInitializeWeights);
	GetDlgItem(IDC_TO_VALUE)->EnableWindow(mInitializeWeights);	
}

BOOL CKohonenPropDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	mNormalizeInputs = pSettings->bNormilizeInputs;

	mInitializeWeights = pSettings->bInitializeWeights;
	if (!mInitializeWeights)
	{
		GetDlgItem(IDC_FROM_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TO_VALUE)->EnableWindow(FALSE);			
	}

	mFromValue = pSettings->fFromValue;
	mToValue = pSettings->fToValue;

	mNormilizeWeights = pSettings->bNormilizeWeights;

	mMaxDistance = pSettings->fMaxDistance;
	mLoopsCount = pSettings->iLoopsCount;

	mStartSpeed = pSettings->fStartSpeed;
	mMultiplier = pSettings->fMultiplier;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CKohonenPropDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	pSettings->bNormilizeInputs = mNormalizeInputs;

	pSettings->bInitializeWeights = mInitializeWeights;

	pSettings->fFromValue = mFromValue;
	pSettings->fToValue = mToValue;

	pSettings->bNormilizeWeights = mNormilizeWeights;

	pSettings->fMaxDistance = mMaxDistance;
	pSettings->iLoopsCount = mLoopsCount;

	pSettings->fStartSpeed = mStartSpeed;
	pSettings->fMultiplier = mMultiplier;

	CDialog::OnOK();
}
