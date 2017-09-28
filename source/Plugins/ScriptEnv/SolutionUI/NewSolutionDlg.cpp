// NewSolutionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\ScriptEnv.h"
#include "NewSolutionDlg.h"
#include ".\newsolutiondlg.h"


// CNewSolutionDlg dialog

IMPLEMENT_DYNAMIC(CNewSolutionDlg, CDialog)
CNewSolutionDlg::CNewSolutionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewSolutionDlg::IDD, pParent)
	, mSolutionName(_T(""))
	, mFileName(_T(""))
{
}

CNewSolutionDlg::~CNewSolutionDlg()
{
}

void CNewSolutionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SOLUTION_NAME, mSolutionName);
	DDX_Text(pDX, IDC_SCRIPT_FILE_NAME, mFileName);
}


BEGIN_MESSAGE_MAP(CNewSolutionDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()


// CNewSolutionDlg message handlers

void CNewSolutionDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Scripts Solution v1.0|*.nlssln||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		UpdateData(TRUE);
		mFileName = mFileDlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CNewSolutionDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	if (mFileName.GetLength() < 1)
	{
		AfxMessageBox("You must select file name to save solution.");
		return;
	}

	if (mSolutionName.GetLength() < 1)
	{
		AfxMessageBox("You must enter solution name.");
		return;
	}

	CDialog::OnOK();
}
