// ProcessHLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HopfieldLearning.h"
#include "ProcessHLDlg.h"

#include "interface_idds.h"
#include ".\processhldlg.h"

// ProcessHLDlg dialog

IMPLEMENT_DYNAMIC(CProcessHLDlg, CDialog)
CProcessHLDlg::CProcessHLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessHLDlg::IDD, pParent)
{
	pAppController = NULL;

	pOnTop = NULL;
}

CProcessHLDlg::~CProcessHLDlg()
{
}

void CProcessHLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINTAB, mMainTab);
}


BEGIN_MESSAGE_MAP(CProcessHLDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, OnTcnSelchangeMaintab)
END_MESSAGE_MAP()


// ProcessHLDlg message handlers

BOOL CProcessHLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("Learning");
	mMainTab.InsertItem(0, &tcItem);

	CRect rect;
	mLearnLayerDlg.SetAppController(pAppController);
	mLearnLayerDlg.Create(CLearnLayerDlg::IDD, &mMainTab);
	mLearnLayerDlg.GetWindowRect(&rect);
	mLearnLayerDlg.MoveWindow(6, 25, rect.Width(), rect.Height());
	mLearnLayerDlg.ShowWindow(SW_SHOW);

	pOnTop = (CDialog*)&mLearnLayerDlg;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProcessHLDlg::OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (pOnTop)
		pOnTop->ShowWindow(SW_HIDE);

    int iCurSel = mMainTab.GetCurSel();
	switch (iCurSel)
	{
	case 0:
		pOnTop = (CDialog*)&mLearnLayerDlg;
		break;
	default:
		pOnTop = NULL;
	}

	if (pOnTop)
		pOnTop->ShowWindow(SW_SHOW);
}
