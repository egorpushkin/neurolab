// CIPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\BuilderElements.h"
#include "CIPropDlg.h"


// CCIPropDlg dialog

IMPLEMENT_DYNAMIC(CCIPropDlg, CDialog)
CCIPropDlg::CCIPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCIPropDlg::IDD, pParent)
	, mValue(0)
{
}

CCIPropDlg::~CCIPropDlg()
{
}

void CCIPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, mValue);
}


BEGIN_MESSAGE_MAP(CCIPropDlg, CDialog)
END_MESSAGE_MAP()


// CCIPropDlg message handlers
