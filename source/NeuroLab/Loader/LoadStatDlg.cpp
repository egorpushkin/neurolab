// LoadStatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\NeuroLab.h"
#include ".\LoadStatDlg.h"

// CLoadStatDlg dialog

IMPLEMENT_DYNAMIC(CLoadStatDlg, CDialog)
CLoadStatDlg::CLoadStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadStatDlg::IDD, pParent)
{
	iLoadState = 0;
}

CLoadStatDlg::~CLoadStatDlg()
{
}

void CLoadStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOAD_STATE_STRING, mStatMess);
}


BEGIN_MESSAGE_MAP(CLoadStatDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CLoadStatDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	if (iLoadState == 1)
	{
		pLoader->LoadComponents();

		SendMessage(WM_CLOSE);
	}
	iLoadState++;
	Invalidate();
}

void CLoadStatDlg::SetComponentsLoader(CComponentsLoader * Loader)
{
	pLoader = Loader;
}

void CLoadStatDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

void CLoadStatDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}
