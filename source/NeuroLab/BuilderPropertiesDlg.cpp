// BuilderPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "BuilderPropertiesDlg.h"
#include ".\builderpropertiesdlg.h"

// CBuilderPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CBuilderPropertiesDlg, CDialog)
CBuilderPropertiesDlg::CBuilderPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuilderPropertiesDlg::IDD, pParent)
	, mShowGrid(FALSE)
	, mGridRange(0)
	, mAttachToGrid(FALSE)
{
}

CBuilderPropertiesDlg::~CBuilderPropertiesDlg()
{
}

void CBuilderPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_SHOW_GRID, mShowGrid);
	DDX_Text(pDX, IDC_GRID_RANGE, mGridRange);
	DDX_Check(pDX, IDC_ATTACH_TO_GRID, mAttachToGrid);
}


BEGIN_MESSAGE_MAP(CBuilderPropertiesDlg, CDialog)
	ON_BN_CLICKED(IDC_SHOW_GRID, OnBnClickedShowGrid)
END_MESSAGE_MAP()


// CBuilderPropertiesDlg message handlers
void CBuilderPropertiesDlg::EnableGridControls(BOOL bEnable)
{
	GetDlgItem(IDC_GRID_RANGE)->EnableWindow(bEnable);
	GetDlgItem(IDC_ATTACH_TO_GRID)->EnableWindow(bEnable);
	GetDlgItem(IDC_GRID_RANGE_TITLE)->EnableWindow(bEnable);
}

BOOL CBuilderPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	EnableGridControls(mShowGrid);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CBuilderPropertiesDlg::OnBnClickedShowGrid()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	EnableGridControls(mShowGrid);	
	if (!mShowGrid)
		mAttachToGrid = FALSE;

	UpdateData(FALSE);
}