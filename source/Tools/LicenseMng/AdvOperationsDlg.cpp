// AdvOperationsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LicenseMng.h"
#include "AdvOperationsDlg.h"
#include ".\advoperationsdlg.h"

#include <Wincrypt.h>

// CAdvOperationsDlg dialog

IMPLEMENT_DYNAMIC(CAdvOperationsDlg, CDialog)
CAdvOperationsDlg::CAdvOperationsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvOperationsDlg::IDD, pParent)
	, mKeyContainerName(_T(""))
{
}

CAdvOperationsDlg::~CAdvOperationsDlg()
{
}

void CAdvOperationsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPERATION_TYPE, mOperationType);
	DDX_Text(pDX, IDC_KEY_CONTAINER_NAME, mKeyContainerName);
}


BEGIN_MESSAGE_MAP(CAdvOperationsDlg, CDialog)
	ON_BN_CLICKED(IDC_PERFORM_OPERATION, OnBnClickedPerformOperation)
END_MESSAGE_MAP()


// CAdvOperationsDlg message handlers

BOOL CAdvOperationsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	mOperationType.AddString(_T("CRYPT_DELETEKEYSET"));
	mOperationType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAdvOperationsDlg::OnBnClickedPerformOperation()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	// Another operations are not supported
	DWORD dwProvType = CRYPT_DELETEKEYSET;

	HCRYPTPROV hProv = NULL;

	if (CryptAcquireContext(&hProv, 
		mKeyContainerName, 
		MS_ENHANCED_PROV, 
		PROV_RSA_FULL, 
		dwProvType))
	{
		AfxMessageBox("Operation completed successfully.");	
	}
}
