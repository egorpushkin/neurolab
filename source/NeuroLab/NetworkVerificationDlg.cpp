// NetworkVerificationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "NetworkVerificationDlg.h"
#include ".\networkverificationdlg.h"

#include "StandartControls\EditListCtrl.h"

#include "CmnFactory.h"

// CNetworkVerificationDlg dialog

IMPLEMENT_DYNAMIC(CNetworkVerificationDlg, CDialog)
CNetworkVerificationDlg::CNetworkVerificationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetworkVerificationDlg::IDD, pParent)
	, pAppController(NULL)
	, mErrorsCount(0)
	, mWarningsCount(0)
{
}

CNetworkVerificationDlg::~CNetworkVerificationDlg()
{
}

void CNetworkVerificationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VERIFICATION_RESULTS, mResultsList);
	DDX_Text(pDX, IDC_ERRORS_COUNT, mErrorsCount);
	DDX_Text(pDX, IDC_WARNINGS_COUNT, mWarningsCount);
}


BEGIN_MESSAGE_MAP(CNetworkVerificationDlg, CDialog)
	ON_BN_CLICKED(IDC_VERIFY, OnBnClickedVerify)
END_MESSAGE_MAP()

void CNetworkVerificationDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// CNetworkVerificationDlg message handlers

void CNetworkVerificationDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CNetworkVerificationDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CNetworkVerificationDlg::OnBnClickedVerify()
{
	// TODO: Add your control notification handler code here
	INetworkVerifier* pNetworkVerifier = NULL;
	pAppController->QueryInterface(IDD_INetworkVerifier, (void**)&pNetworkVerifier);

	if (!pNetworkVerifier)
	{
		AddLogMessage(CString(_T("ESys")), CString(_T("Cannot access network verification mechanism.")), CString(_T("Environment")));
		return;
	}

	ILogProvider* pLogProvider = NULL;
	QueryInterface(IDD_ILogProvider, (void**)&pLogProvider);

	UpdateData(TRUE);
	
	pNetworkVerifier->VerifyNetwork(mErrorsCount, mWarningsCount, pLogProvider);

    UpdateData(FALSE);	
}

BOOL CNetworkVerificationDlg::Create(int IDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(IDD, pParentWnd);

    if (bRet)
	{
		ASSERT(pAppController != NULL);

		CRect	rect;
		mResultsList.GetClientRect(&rect);

		mResultsList.InsertColumn(0, _T("Type"), LVCFMT_LEFT,  rect.Width()*7/80); 
		mResultsList.InsertColumn(1, _T("Description"), LVCFMT_LEFT,  rect.Width()*27/40); 
		mResultsList.InsertColumn(2, _T("Section"), LVCFMT_LEFT,  rect.Width()*15/80); 
		mResultsList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}

	return bRet;
}

// ILogProvider implementations section
void CNetworkVerificationDlg::ClearLog()
{
	mResultsList.DeleteAllItems();
}

void CNetworkVerificationDlg::AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection)
{
	AddListItem(&mResultsList, -1, NULL, 3, MessageType, Message, MessageSection);
}

// IObject implementations section
CString CNetworkVerificationDlg::GetClassString()
{
	return _T("CNetworkVerificationDlg");
}

void CNetworkVerificationDlg::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ILogProvider:
		*ppvObject = (ILogProvider*)this;
		break;
	}
}