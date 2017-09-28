// FannAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FannAboutDlg.h"


// CFannAboutDlg dialog

IMPLEMENT_DYNAMIC(CFannAboutDlg, CDialog)
CFannAboutDlg::CFannAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFannAboutDlg::IDD, pParent)
{
}

CFannAboutDlg::~CFannAboutDlg()
{
}

void CFannAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFannAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFannAboutDlg message handlers
