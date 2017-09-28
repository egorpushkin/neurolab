// NewGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../DataCreator.h"
#include "NewGroupDlg.h"
#include ".\newgroupdlg.h"


// CNewGroupDlg dialog

IMPLEMENT_DYNAMIC(CNewGroupDlg, CDialog)
CNewGroupDlg::CNewGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGroupDlg::IDD, pParent)
	, mGroupName(_T(""))
{
	mWmdTitle = _T("");
}

CNewGroupDlg::~CNewGroupDlg()
{
}

void CNewGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GROUP_NAME, mGroupName);
}


BEGIN_MESSAGE_MAP(CNewGroupDlg, CDialog)
END_MESSAGE_MAP()


// CNewGroupDlg message handlers

void CNewGroupDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	UpdateData(TRUE);

	if (mGroupName.GetLength() < 1)
	{
		AfxMessageBox("Enter group name.");
		return;
	}

	CDialog::OnOK();
}

BOOL CNewGroupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	if (mWmdTitle != _T(""))
		SetWindowText(mWmdTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
