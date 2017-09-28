// TrainerPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../PCATrainer.h"
#include "TrainerPropertiesDlg.h"
#include ".\trainerpropertiesdlg.h"


// CTrainerPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CTrainerPropertiesDlg, CDialog)
CTrainerPropertiesDlg::CTrainerPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainerPropertiesDlg::IDD, pParent)
	, mVectorsCount(0)
	, pSettings(NULL)
{
}

CTrainerPropertiesDlg::~CTrainerPropertiesDlg()
{
}

void CTrainerPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VECTORS_COUNT, mVectorsCount);
}


BEGIN_MESSAGE_MAP(CTrainerPropertiesDlg, CDialog)
END_MESSAGE_MAP()


// CTrainerPropertiesDlg message handlers

BOOL CTrainerPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pSettings != NULL);

	if (pSettings->iMethod == M_JACOBI)
	{
		((CButton*)GetDlgItem(IDC_JACOBI_DECOMP))->SetCheck(BST_CHECKED);
	} else if (pSettings->iMethod == M_HOUSEHOLDER)
	{
		((CButton*)GetDlgItem(IDC_HOUSEHOLDER_DECOMP))->SetCheck(BST_CHECKED);
	}

	mVectorsCount = pSettings->iFeaturesCount;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTrainerPropertiesDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mVectorsCount <= 0)
	{
		AfxMessageBox(_T("You must enter positive value for eigenvectors' count field."));
		return;
	}

	pSettings->iFeaturesCount = mVectorsCount;

	if (((CButton*)GetDlgItem(IDC_JACOBI_DECOMP))->GetCheck() == BST_CHECKED)
	{
		pSettings->iMethod = M_JACOBI;
	} else if (((CButton*)GetDlgItem(IDC_HOUSEHOLDER_DECOMP))->GetCheck() == BST_CHECKED)
	{
		pSettings->iMethod = M_HOUSEHOLDER;
	}

	CDialog::OnOK();
}
