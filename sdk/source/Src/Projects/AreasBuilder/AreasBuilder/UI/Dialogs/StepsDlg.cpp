// StepsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../../AreasBuilder.h"
#include "StepsDlg.h"
#include ".\stepsdlg.h"

// CStepsDlg dialog

IMPLEMENT_DYNAMIC(CStepsDlg, CDialog)
CStepsDlg::CStepsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStepsDlg::IDD, pParent)
{
}

CStepsDlg::~CStepsDlg()
{
}

void CStepsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IWB_STEPS_CTRL, browserControl_);
}


BEGIN_MESSAGE_MAP(CStepsDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CStepsDlg message handlers

void CStepsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (browserControl_.GetSafeHwnd())
	{
		browserControl_.MoveWindow(0, 0, cx, cy);
	}
}

BOOL CStepsDlg::Create(UINT resourceId, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ret = CDialog::Create(resourceId, pParentWnd);

	if (ret)
	{
		GetModuleFileName(GetModuleHandle(NULL), appFolder_.GetBuffer(MAX_PATH), MAX_PATH);
		appFolder_.ReleaseBuffer();
		int tmPos = appFolder_.ReverseFind('\\');
		appFolder_	= appFolder_.Left(tmPos);	

		CString helpPage = 
			appFolder_ + 
			CString(_T("/UserGuide/steps.htm"));

		browserControl_.Navigate(helpPage, NULL, NULL, NULL, NULL);
	}

	return ret;
}

void CStepsDlg::OnOK()
{
}

void CStepsDlg::OnCancel()
{
}
