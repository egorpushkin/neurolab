// ProcessMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessNetwork.h"
#include "ProcessMainDlg.h"
#include ".\processmaindlg.h"


// CProcessMainDlg dialog

IMPLEMENT_DYNAMIC(CProcessMainDlg, CDialog)
CProcessMainDlg::CProcessMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessMainDlg::IDD, pParent)
{
	pOnTop = NULL;
}

CProcessMainDlg::~CProcessMainDlg()
{
}

void CProcessMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, mMainTab);
}


BEGIN_MESSAGE_MAP(CProcessMainDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, OnTcnSelchangeMainTab)
END_MESSAGE_MAP()

void CProcessMainDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// CProcessMainDlg message handlers

BOOL CProcessMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("Linear Processing");
	mMainTab.InsertItem(0, &tcItem);

	tcItem.pszText = _T("Visual Processing");
	mMainTab.InsertItem(1, &tcItem);

	tcItem.pszText = _T("Signals Processing");
	mMainTab.InsertItem(2, &tcItem);


	CRect rect;
	mProcessNetworkDlg.SetAppController(pAppController);
	mProcessNetworkDlg.Create(CProcessNetworkDlg::IDD, &mMainTab);
	mProcessNetworkDlg.GetWindowRect(&rect);
	mProcessNetworkDlg.MoveWindow(3, 23, rect.Width(), rect.Height());
	mProcessNetworkDlg.ShowWindow(SW_SHOW);

	pOnTop = &mProcessNetworkDlg;

	mProcessVisualDlg.SetAppController(pAppController);
	mProcessVisualDlg.Create(CProcessVisualDlg::IDD, &mMainTab);
	mProcessVisualDlg.GetWindowRect(&rect);
	mProcessVisualDlg.MoveWindow(3, 23, rect.Width(), rect.Height());

	mProcessSignalsDlg.SetAppController(pAppController);
	mProcessSignalsDlg.Create(CProcessSignalsDlg::IDD, &mMainTab);
	mProcessSignalsDlg.GetWindowRect(&rect);
	mProcessSignalsDlg.MoveWindow(3, 23, rect.Width(), rect.Height());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProcessMainDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (pOnTop)
		pOnTop->ShowWindow(SW_HIDE);

	int iCurSel = mMainTab.GetCurSel();
	switch (iCurSel)
	{
	case 0:
		pOnTop = &mProcessNetworkDlg;
		break;
	case 1:
		pOnTop = &mProcessVisualDlg;
		break;
	case 2:
		pOnTop = &mProcessSignalsDlg;
		break;
	}

	if (pOnTop)
		pOnTop->ShowWindow(SW_SHOW);
}
