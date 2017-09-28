// SriptingElementCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\..\ScriptsNet.h"
#include "ScriptingElementCodeDlg.h"
#include ".\scriptingelementcodedlg.h"


// CScriptingElementCodeDlg dialog

IMPLEMENT_DYNAMIC(CScriptingElementCodeDlg, CDialog)
CScriptingElementCodeDlg::CScriptingElementCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptingElementCodeDlg::IDD, pParent)
	, mScriptCode(_T(""))
{
}

CScriptingElementCodeDlg::~CScriptingElementCodeDlg()
{
}

void CScriptingElementCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCRIPT_CODE, mScriptCode);
}


BEGIN_MESSAGE_MAP(CScriptingElementCodeDlg, CDialog)
END_MESSAGE_MAP()


// CScriptingElementCodeDlg message handlers

BOOL CScriptingElementCodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	BOOL bRet = mWorkspaceFont.CreateFont(
		14,							// nHeight
		0,							// nWidth
		0,							// nEscapement
		0,							// nOrientation
		FW_NORMAL,					// nWeight
		FALSE,						// bItalic
		FALSE,						// bUnderline
		0,							// cStrikeOut
		ANSI_CHARSET,				// nCharSet
		OUT_DEFAULT_PRECIS,			// nOutPrecision
		CLIP_DEFAULT_PRECIS,		// nClipPrecision
		DEFAULT_QUALITY,			// nQuality
		DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
		_T("Courier New")); 
	GetDlgItem(IDC_SCRIPT_CODE)->SetFont(&mWorkspaceFont);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
