// DataImageCtrlPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataImageCtrlPropDlg.h"
#include ".\dataimagectrlpropdlg.h"


// CDataImageCtrlPropDlg dialog

IMPLEMENT_DYNAMIC(CDataImageCtrlPropDlg, CDialog)
CDataImageCtrlPropDlg::CDataImageCtrlPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataImageCtrlPropDlg::IDD, pParent)
	, mDataLength(0)
	, mXDimension(0)
	, mYDimension(0)
	, mMinDataValue(0)
	, mMaxDataValue(0)
	, mRedComponent(0)
	, mGreenComponent(0)
	, mBlueComponent(0)
	, mUseRedMask(FALSE)
	, mUseGreenMask(FALSE)
	, mUseBlueMask(FALSE)
	, mShowGrid(FALSE)
	, mShowInfo(FALSE)
{
}

CDataImageCtrlPropDlg::~CDataImageCtrlPropDlg()
{
}

void CDataImageCtrlPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_LENGTH, mDataLength);
	DDX_Text(pDX, IDC_XDIMENSION, mXDimension);
	DDX_Text(pDX, IDC_YDIMENSION, mYDimension);
	DDX_Text(pDX, IDC_MIN_DATA_VALUE, mMinDataValue);
	DDX_Text(pDX, IDC_MAX_DATA_VALUE, mMaxDataValue);
	DDX_Text(pDX, IDC_RED_COMPONENT_VALUE, mRedComponent);
	DDX_Text(pDX, IDC_GREEN_COMPONENT_VALUE, mGreenComponent);
	DDX_Text(pDX, IDC_BLUE_COMPONENT_VALUE, mBlueComponent);
	DDX_Check(pDX, IDC_USE_MASK_RED, mUseRedMask);
	DDX_Check(pDX, IDC_USE_MASK_GREEN, mUseGreenMask);
	DDX_Check(pDX, IDC_USE_MASK_BLUE, mUseBlueMask);
	DDX_Control(pDX, IDC_RED_COMPONENT_VALUE, mRedComponentCtrl);
	DDX_Control(pDX, IDC_GREEN_COMPONENT_VALUE, mGreenComponentCtrl);
	DDX_Control(pDX, IDC_BLUE_COMPONENT_VALUE, mBlueComponentCtrl);
	DDX_Check(pDX, IDC_SHOW_GRID, mShowGrid);
	DDX_Check(pDX, IDC_SHOW_INFO, mShowInfo);
}


BEGIN_MESSAGE_MAP(CDataImageCtrlPropDlg, CDialog)
	ON_BN_CLICKED(IDC_USE_MASK_RED, OnBnClickedUseMaskRed)
	ON_BN_CLICKED(IDC_USE_MASK_GREEN, OnBnClickedUseMaskGreen)
	ON_BN_CLICKED(IDC_USE_MASK_BLUE, OnBnClickedUseMaskBlue)
END_MESSAGE_MAP()


// CDataImageCtrlPropDlg message handlers

void CDataImageCtrlPropDlg::OnBnClickedUseMaskRed()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	mRedComponentCtrl.EnableWindow(!mUseRedMask);
}

void CDataImageCtrlPropDlg::OnBnClickedUseMaskGreen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	mGreenComponentCtrl.EnableWindow(!mUseGreenMask);
}

void CDataImageCtrlPropDlg::OnBnClickedUseMaskBlue()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	mBlueComponentCtrl.EnableWindow(!mUseBlueMask);
}

BOOL CDataImageCtrlPropDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if (mUseRedMask)
		mRedComponentCtrl.EnableWindow(FALSE);
	if (mUseGreenMask)
		mGreenComponentCtrl.EnableWindow(FALSE);
	if (mUseBlueMask)
		mBlueComponentCtrl.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDataImageCtrlPropDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	if (mXDimension == 0)
	{
		AfxMessageBox("X dimension cannot equals to zero.");
		return;
	}

	if (mYDimension == 0)
	{
		AfxMessageBox("Y dimension cannot equals to zero.");
		return;
	}

	if (mDataLength > mXDimension*mYDimension)
	{
		AfxMessageBox("Result grid is not enough for presenting all necessary data.");
		return;
	}

	if (mMinDataValue >= mMaxDataValue)
	{
		AfxMessageBox("Minimum data value cannot be less or equal to maximim value.");
		return;
	}

	CDialog::OnOK();
}
