// ExportDetailsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetworkExporter.h"
#include "ExportDetailsDlg.h"
#include ".\exportdetailsdlg.h"


// CExportDetailsDlg dialog

IMPLEMENT_DYNAMIC(CExportDetailsDlg, CDialog)
CExportDetailsDlg::CExportDetailsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportDetailsDlg::IDD, pParent)
	, pExportSolution(NULL)
	, mVersion(_T(""))
	, mType(_T(""))
	, mDescription(_T(""))
{
}

CExportDetailsDlg::~CExportDetailsDlg()
{
}

void CExportDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOLUTION_TREE, mSolutionTree);
	DDX_Text(pDX, IDC_VERSION, mVersion);
	DDX_Text(pDX, IDC_TYPE, mType);
	DDX_Text(pDX, IDC_DESCRIPTION, mDescription);
}


BEGIN_MESSAGE_MAP(CExportDetailsDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_SOLUTION_TREE, OnTvnSelchangedSolutionTree)
END_MESSAGE_MAP()


// CExportDetailsDlg message handlers

BOOL CExportDetailsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pExportSolution != NULL);

	mImageList.Create(16, 16, TRUE, 1, 1);
	mImageList.Add(AfxGetApp()->LoadIcon(IDI_ROOT_ITEM));
	mImageList.Add(AfxGetApp()->LoadIcon(IDI_GROUP_ITEM));
	mImageList.Add(AfxGetApp()->LoadIcon(IDI_BINARY_ITEM));
	mImageList.Add(AfxGetApp()->LoadIcon(IDI_COMPRESSED_ITEM));
	mImageList.Add(AfxGetApp()->LoadIcon(IDI_TEXT_ITEM));
	mImageList.Add(AfxGetApp()->LoadIcon(IDI_PROJECT_ITEM));

	mSolutionTree.SetImageList(&mImageList, LVSIL_SMALL);
	mSolutionTree.SetImageList(&mImageList, TVSIL_NORMAL);

	ShowSolution();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CExportDetailsDlg::ShowSolution()
{
	HTREEITEM htiRoot = mSolutionTree.InsertItem(_T("Export Symbols"), 0, 0);

	pExportSolution->CreateEnumerator();
	while (CExportGroup* pExportGroup = pExportSolution->GetNextGroup())
	{
		HTREEITEM htiGroup = mSolutionTree.InsertItem(
			pExportGroup->csGroupName, 1, 1, htiRoot);
		mSolutionTree.SetItemData(htiGroup, (DWORD_PTR)pExportGroup);

		pExportGroup->CreateEnumerator();
		while (CExportItem* pExportItem = pExportGroup->GetNextItem())
		{	
			int iIconIndex = 4;
			if (pExportItem->csItemType == _T("bin"))
				iIconIndex = 2;
			else if (pExportItem->csItemType == _T("compressed"))
				iIconIndex = 3;
			else if (pExportItem->csItemType == _T("text"))
				iIconIndex = 4;
			else if (pExportItem->csItemType == _T("project"))
				iIconIndex = 5;

			HTREEITEM htiItem = mSolutionTree.InsertItem(
				pExportItem->csItemName, iIconIndex, iIconIndex, htiGroup);
			mSolutionTree.SetItemData(htiItem, (DWORD_PTR)pExportItem);
		}
	
		mSolutionTree.Expand(htiGroup, TVE_EXPAND);
	}

	mSolutionTree.Expand(htiRoot, TVE_EXPAND);
}

void CExportDetailsDlg::ShowSolutionItem(IObject* pItemObject)
{
	if (!pItemObject)
	{
		UpdateData(TRUE);
		mVersion = _T("");
		mType = _T("");
		mDescription = _T("");	
		UpdateData(FALSE);

		return;
	}

	UpdateData(TRUE);
	if (pItemObject->GetClassString() == _T("CExportItem"))
	{
		CExportItem* pExportItem = (CExportItem*)pItemObject;

		mVersion = pExportItem->csItemVersion;
		mType = pExportItem->csItemType;
		mDescription = pExportItem->csItemDescription;				
	} else if (pItemObject->GetClassString() == _T("CExportGroup"))
	{
		CExportGroup* pExportGroup = (CExportGroup*)pItemObject;

		mVersion = _T("");
		mType = _T("group");
		mDescription = _T("");				
	}
	UpdateData(FALSE);
}

void CExportDetailsDlg::OnTvnSelchangedSolutionTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM htiSelected = mSolutionTree.GetSelectedItem();
	if (htiSelected)
	{
		IObject* pItemObject = (IObject*)mSolutionTree.GetItemData(htiSelected);
		ShowSolutionItem(pItemObject);
	}
}
