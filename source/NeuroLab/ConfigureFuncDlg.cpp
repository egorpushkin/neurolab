// ConfigureFuncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "ConfigureFuncDlg.h"
#include ".\configurefuncdlg.h"

bool	IsEnableEditItems(int	iItem, int	iSubItem)
{
	if (iSubItem == 1)
		return true;
	return false;	
}

// CConfigureFuncDlg dialog

IMPLEMENT_DYNAMIC(CConfigureFuncDlg, CDialog)
CConfigureFuncDlg::CConfigureFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigureFuncDlg::IDD, pParent)
	, mFuncExpr(_T(""))
{
//	pFunction = NULL;
}

CConfigureFuncDlg::~CConfigureFuncDlg()
{
}

void CConfigureFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mParameters);
	DDX_Text(pDX, IDC_FUNCTIONEXPRESSION, mFuncExpr);
}


BEGIN_MESSAGE_MAP(CConfigureFuncDlg, CDialog)
END_MESSAGE_MAP()


// CConfigureFuncDlg message handlers

BOOL CConfigureFuncDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect	rect;
	mParameters.GetClientRect(&rect);

	mParameters.InsertColumn(0, _T("Parameter"), LVCFMT_LEFT,  rect.Width()*4/10); 
	mParameters.InsertColumn(1, _T("Value"), LVCFMT_LEFT,  rect.Width()*6/10); 
	mParameters.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mParameters.SetVerifyingFunc(IsEnableEditItems);

	if (!pFunction)
	{
		AfxMessageBox("Wrong dialog initialization!");
		EndDialog(IDCANCEL);
	}

	CString	tmValue;
	for (POSITION pos = pFunction->mParameters.GetHeadPosition();pos;)
	{
		sParameter* tmParam = pFunction->mParameters.GetNext(pos);

		tmValue.Format("%f", tmParam->fValue);
		AddListItem(&mParameters, -1, (LPARAM)tmParam, 2, tmParam->csParamName, tmValue);	
	}

	if (pFunction->mParameters.GetCount()==0)
	{
		AfxMessageBox("There is no parameters that can be configured.");
		EndDialog(IDCANCEL);
	}

	GetWindowText(tmValue);
	SetWindowText(tmValue + CString(" ") + CString(pFunction->csTitle));

	mFuncExpr = pFunction->csExpression;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigureFuncDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	char tmValue[100];
	for (int i = 0;i<mParameters.GetItemCount();i++)
	{
		sParameter* tmParam = (sParameter *)mParameters.GetItemData(i);
		mParameters.GetItemText(i, 1, tmValue, 100);
		
		tmParam->fValue = atof(tmValue);
	}

	CDialog::OnOK();
}
