// SelectCollectionGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "SelectCollectionGroupDlg.h"
#include ".\selectcollectiongroupdlg.h"


// CSelectCollectionGroupDlg dialog

IMPLEMENT_DYNAMIC(CSelectCollectionGroupDlg, CDialog)
CSelectCollectionGroupDlg::CSelectCollectionGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCollectionGroupDlg::IDD, pParent)
	, mGroupName(_T(""))
	, mDataItems(0)
	, mSubgroups(0)
{
	pDataCollection = NULL;
	iCtrlMode == SCG_MODE_VIEW;
}

CSelectCollectionGroupDlg::~CSelectCollectionGroupDlg()
{
}

void CSelectCollectionGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLLECTION_GROUPS_TREE, mGroupsTree);
	DDX_Text(pDX, IDC_GROUP_NAME, mGroupName);
	DDX_Text(pDX, IDC_DATA_ITEMS, mDataItems);
	DDX_Text(pDX, IDC_SUBGROUPS, mSubgroups);
}


BEGIN_MESSAGE_MAP(CSelectCollectionGroupDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_COLLECTION_GROUPS_TREE, OnTvnSelchangedCollectionGroupsTree)
END_MESSAGE_MAP()


// CSelectCollectionGroupDlg message handlers

void CSelectCollectionGroupDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (iCtrlMode == SCG_MODE_SELEECT)
	{
		UpdateData(TRUE);

		if (mGroupName == _T(""))
		{
			AfxMessageBox("You must select group!");
			return;
		}	
	}

	CDialog::OnOK();
}

BOOL CSelectCollectionGroupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pDataCollection != NULL);

	// Building groups tree
	HTREEITEM htiRoot = mGroupsTree.InsertItem(
		pDataCollection->GetCollectionGroup()->GetGroupName());
	mGroupsTree.SetItemData(htiRoot, (DWORD_PTR)pDataCollection->GetCollectionGroup());

	ShowSubgroups(pDataCollection->GetCollectionGroup(), htiRoot);

	if (iCtrlMode == SCG_MODE_VIEW)
		SetWindowText("Collection groups");	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectCollectionGroupDlg::ShowSubgroups(CCollectionGroup* pGroup, HTREEITEM htiParent)
{
	pGroup->CreateEnumerator();
	while (CCollectionGroup* pCurGroup = pGroup->GetNextGroup())
	{
		HTREEITEM htiGroup = mGroupsTree.InsertItem(
			pCurGroup->GetGroupName(), htiParent);
		mGroupsTree.SetItemData(htiGroup, (DWORD_PTR)pCurGroup);

		ShowSubgroups(pCurGroup, htiGroup);	
	}

	mGroupsTree.Expand(htiParent, TVE_EXPAND);
}

void CSelectCollectionGroupDlg::OnTvnSelchangedCollectionGroupsTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	CCollectionGroup* pCurGroup = NULL;
	
	HTREEITEM htiSelected = mGroupsTree.GetSelectedItem();
	if (htiSelected)
		pCurGroup = (CCollectionGroup*)mGroupsTree.GetItemData(htiSelected);

	ShowGroupInformation(pCurGroup);

	*pResult = 0;
}

void CSelectCollectionGroupDlg::ShowGroupInformation(CCollectionGroup* pGroup)
{
	UpdateData(TRUE);

	if (pGroup)
	{
		mGroupName = pGroup->GetGroupName();
		mDataItems = pGroup->GetDataArray()->GetItemsCount();
		mSubgroups = pGroup->GetGroupsCount();	
	} else
	{
		mGroupName = _T("");
		mDataItems = 0;
		mSubgroups = 0;	
	}

	UpdateData(FALSE);
}

void CSelectCollectionGroupDlg::SetDataCollection(IDataCollection* pCollection)
{
	pDataCollection = pCollection;
}

void CSelectCollectionGroupDlg::SetCtrlMode(int Mode)
{
	iCtrlMode = Mode;
}
