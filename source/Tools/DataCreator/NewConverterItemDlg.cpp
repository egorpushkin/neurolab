// NewConverterItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "NewConverterItemDlg.h"
#include ".\newconverteritemdlg.h"

#include "SelectDataSymbolDlg.h"
#include "SelectCollectionGroupDlg.h"

// CNewConverterItemDlg dialog

IMPLEMENT_DYNAMIC(CNewConverterItemDlg, CDialog)
CNewConverterItemDlg::CNewConverterItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewConverterItemDlg::IDD, pParent)
	, mGroupName(_T(""))
	, mSymbolIndex(-1)
{
	pDataFile = NULL;
	pDataCollection = NULL;
}

CNewConverterItemDlg::~CNewConverterItemDlg()
{
}

void CNewConverterItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COLL_GROUP_NAME, mGroupName);
	DDX_Text(pDX, IDC_SYMBOL_INDEX, mSymbolIndex);
}


BEGIN_MESSAGE_MAP(CNewConverterItemDlg, CDialog)
	ON_BN_CLICKED(IDC_SELECT_GROUP_NAME, OnBnClickedSelectGroupName)
	ON_BN_CLICKED(IDC_SELECT_SYMBOL_INDEX, OnBnClickedSelectSymbolIndex)
END_MESSAGE_MAP()


// CNewConverterItemDlg message handlers

void CNewConverterItemDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mSymbolIndex == -1)
	{
		AfxMessageBox("You must select symbol to add converter item.");	
		return;
	}

	if (mGroupName == _T(""))
	{
		AfxMessageBox("You must select collection group to add converter item.");	
		return;
	}

	CDialog::OnOK();
}

void CNewConverterItemDlg::OnBnClickedSelectGroupName()
{
	// TODO: Add your control notification handler code here
	ASSERT(pDataFile != NULL);

	UpdateData(TRUE);

	CSelectCollectionGroupDlg mDlg;

	mDlg.SetDataCollection(pDataCollection);
	mDlg.SetCtrlMode(SDS_MODE_SELEECT);
	mDlg.mGroupName = mGroupName;

	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		mGroupName = mDlg.mGroupName;

		UpdateData(FALSE);
	}
}

void CNewConverterItemDlg::OnBnClickedSelectSymbolIndex()
{
	// TODO: Add your control notification handler code here
	ASSERT(pDataFile != NULL);

	UpdateData(TRUE);

	CSelectDataSymbolDlg mDlg;
	
	mDlg.SetDataFile(pDataFile, false);
	mDlg.SetCtrlMode(SDS_MODE_SELEECT);
	mDlg.mSymbolIndex = mSymbolIndex;
	
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		mSymbolIndex = mDlg.mSymbolIndex;

		UpdateData(FALSE);
	}
}

void CNewConverterItemDlg::SetDataFile(IDataFile* pFile)
{
	pDataFile = pFile;
}

void CNewConverterItemDlg::SetDataCollection(IDataCollection* pCollection)
{
	pDataCollection = pCollection;
}