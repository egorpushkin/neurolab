// NewScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\ScriptEnv.h"
#include "NewScriptDlg.h"
#include ".\newscriptdlg.h"


// CNewScriptDlg dialog

IMPLEMENT_DYNAMIC(CNewScriptDlg, CDialog)
CNewScriptDlg::CNewScriptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewScriptDlg::IDD, pParent)
	, mFileName(_T(""))
{
	bNewScript = true;
}

CNewScriptDlg::~CNewScriptDlg()
{
}

void CNewScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCRIPT_FILE_NAME, mFileName);
}


BEGIN_MESSAGE_MAP(CNewScriptDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()


// CNewScriptDlg message handlers

void CNewScriptDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(!bNewScript, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Script v1.0|*.nlsfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		UpdateData(TRUE);
		mFileName = mFileDlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CNewScriptDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	if (mFileName.GetLength() < 1)
	{
		AfxMessageBox("You must select file name to save new script file.");
		return;
	}

	CDialog::OnOK();
}