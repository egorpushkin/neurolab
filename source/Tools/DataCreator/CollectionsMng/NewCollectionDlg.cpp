// NewCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\DataCreator.h"
#include "NewCollectionDlg.h"
#include ".\newcollectiondlg.h"

// CNewCollectionDlg dialog

IMPLEMENT_DYNAMIC(CNewCollectionDlg, CDialog)
CNewCollectionDlg::CNewCollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCollectionDlg::IDD, pParent)
	, mCollectionName(_T(""))
{
	mWmdTitle = _T("");
}

CNewCollectionDlg::~CNewCollectionDlg()
{
}

void CNewCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COLLECTION_NAME, mCollectionName);
}


BEGIN_MESSAGE_MAP(CNewCollectionDlg, CDialog)
END_MESSAGE_MAP()


// CNewCollectionDlg message handlers

BOOL CNewCollectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	if (mWmdTitle != _T(""))
		SetWindowText(mWmdTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNewCollectionDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mCollectionName.GetLength() < 1)
	{
		AfxMessageBox("Enter collection name.");
		return;
	}

	CDialog::OnOK();
}
