// VerificationSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatVerifier.h"
#include "VerificationSettingsDlg.h"
#include ".\verificationsettingsdlg.h"


// CVerificationSettingsDlg dialog

IMPLEMENT_DYNAMIC(CVerificationSettingsDlg, CDialog)
CVerificationSettingsDlg::CVerificationSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVerificationSettingsDlg::IDD, pParent)
	, mMaxError(0)
{
	pSettings = NULL;
}

CVerificationSettingsDlg::~CVerificationSettingsDlg()
{
}

void CVerificationSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAX_ERROR, mMaxError);
}


BEGIN_MESSAGE_MAP(CVerificationSettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_CONDITION_EQUAL, OnBnClickedConditionEqual)
	ON_BN_CLICKED(IDC_CONDITION_COINSIDE, OnBnClickedConditionCoinside)
	ON_BN_CLICKED(IDC_CONDITION_ERROR, OnBnClickedConditionError)
END_MESSAGE_MAP()


// CVerificationSettingsDlg message handlers

BOOL CVerificationSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pSettings != NULL);

	switch(pSettings->iCondition)
	{
	case VS_CONDITION_EQUAL:
		
		((CButton*)GetDlgItem(IDC_CONDITION_EQUAL))->SetCheck(BST_CHECKED);
		EnableMaxError(FALSE);

		break;
	case VS_CONDITION_COINSIDE:

		((CButton*)GetDlgItem(IDC_CONDITION_COINSIDE))->SetCheck(BST_CHECKED);
		EnableMaxError(FALSE);

		break;
	case VS_CONDITION_ERROR:

		((CButton*)GetDlgItem(IDC_CONDITION_ERROR))->SetCheck(BST_CHECKED);
		EnableMaxError(TRUE);

		break;
	}

	mMaxError = pSettings->fMaxError;
	mVerifMode = pSettings->iCondition;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVerificationSettingsDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(pSettings != NULL);

	UpdateData(TRUE);

	pSettings->fMaxError = mMaxError;
	pSettings->iCondition = mVerifMode;

	CDialog::OnOK();
}

void CVerificationSettingsDlg::OnBnClickedConditionEqual()
{
	// TODO: Add your control notification handler code here
	EnableMaxError(FALSE);
	mVerifMode = VS_CONDITION_EQUAL;
}

void CVerificationSettingsDlg::OnBnClickedConditionCoinside()
{
	// TODO: Add your control notification handler code here
	EnableMaxError(FALSE);
	mVerifMode = VS_CONDITION_COINSIDE;
}

void CVerificationSettingsDlg::OnBnClickedConditionError()
{
	// TODO: Add your control notification handler code here
	EnableMaxError(TRUE);
	mVerifMode = VS_CONDITION_ERROR;
}

void CVerificationSettingsDlg::EnableMaxError(BOOL bEnable)
{
	GetDlgItem(IDC_MAX_ERROR)->EnableWindow(bEnable);
}
