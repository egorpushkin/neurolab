// DataImagePropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\..\EdgeDetectors.h"
#include "DataImagePropertiesDlg.h"
#include ".\dataimagepropertiesdlg.h"


// CDataImagePropertiesDlg dialog

IMPLEMENT_DYNAMIC(CDataImagePropertiesDlg, CDialog)
CDataImagePropertiesDlg::CDataImagePropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataImagePropertiesDlg::IDD, pParent)
	, mWidth(0)
	, mHeight(0)
	, mDataLength(0)
{
}

CDataImagePropertiesDlg::~CDataImagePropertiesDlg()
{
}

void CDataImagePropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, mWidth);
	DDX_Text(pDX, IDC_HEIGHT, mHeight);
	DDX_Text(pDX, IDC_DATA_LENGTH, mDataLength);
}


BEGIN_MESSAGE_MAP(CDataImagePropertiesDlg, CDialog)
	ON_EN_CHANGE(IDC_WIDTH, OnEnChangeWidth)
	ON_EN_CHANGE(IDC_HEIGHT, OnEnChangeHeight)
END_MESSAGE_MAP()


// CDataImagePropertiesDlg message handlers

void CDataImagePropertiesDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mWidth <= 0 || mHeight <= 0)
	{
		AfxMessageBox("You must enter valid image width and height.");	
		return;
	}

	CDialog::OnOK();
}

void CDataImagePropertiesDlg::OnEnChangeWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateProperties();
}

void CDataImagePropertiesDlg::OnEnChangeHeight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateProperties();
}

void CDataImagePropertiesDlg::UpdateProperties()
{
	UpdateData(TRUE);

	mDataLength = mWidth * mHeight;

	UpdateData(FALSE);
}
BOOL CDataImagePropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateProperties();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
