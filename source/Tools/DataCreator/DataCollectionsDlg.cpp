// DataCollectionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "DataCollectionsDlg.h"
#include ".\datacollectionsdlg.h"

// CDataCollectionsDlg dialog

IMPLEMENT_DYNAMIC(CDataCollectionsDlg, CDialog)
CDataCollectionsDlg::CDataCollectionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataCollectionsDlg::IDD, pParent)
{
	htiCollectionRoot = NULL;

	pCurrentGroup = NULL;
	pCurrentDataItem = NULL;

	bModified = false;
}

CDataCollectionsDlg::~CDataCollectionsDlg()
{
}

void CDataCollectionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLLECTION_TREE, mCollectionTree);
	DDX_Control(pDX, IDC_COLLECTION_PROPERTIES, mCollectionProperties);
}


BEGIN_MESSAGE_MAP(CDataCollectionsDlg, CDialog)	
END_MESSAGE_MAP()


// CDataCollectionsDlg message handlers

BOOL CDataCollectionsDlg::Create(int IDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(IDD, pParentWnd);

	if (bRet)
	{
		GetApplicationFolder();
		
		InitializeCollectionSolution();
		InitializeWebControlStates();

		ShowLogoScreen();
	}

	return bRet;
}

void CDataCollectionsDlg::GetApplicationFolder()
{
	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);
}

void CDataCollectionsDlg::ShowLogoScreen()
{	
	mCollectionProperties.ShowState(CString("Index"));
}

void CDataCollectionsDlg::InitializeWebControlStates()
{
	mCollectionProperties.AddState(CString("Index"), 
		csAppFolder + CString("\\Media\\DataCreator\\Index.htm"));

	CWebControlState* pState = mCollectionProperties.AddState(CString("Process"), 
		csAppFolder + CString("\\Media\\DataCreator\\Process.htm"));
	pState->AddInvokeShell(CString("new_collection"), OnNewCollection, (DWORD)this);
	pState->AddInvokeShell(CString("load_collection"), OnLoadCollection, (DWORD)this);
	pState->AddInvokeShell(CString("save_collection"), OnSaveCollection, (DWORD)this);
	pState->AddInvokeShell(CString("close_collection"), OnCloseCollection, (DWORD)this);

	pState = mCollectionProperties.AddState(CString("Collection"), 
		csAppFolder + CString("\\Media\\DataCreator\\Collection.htm"));
	pState->AddInvokeShell(CString("edit_collection_name"), OnChangeCollectionName, (DWORD)this);
	pState->AddInvokeShell(CString("show_collection_global_group"), OnShowCollectionGlobalGroup, (DWORD)this);
	pState->SetGetPropertyCallback(GetPropertyCollection, (DWORD)this);

	pState = mCollectionProperties.AddState(CString("About"), 
		csAppFolder + CString("\\Media\\DataCreator\\About.htm"));

	pState = mCollectionProperties.AddState(CString("Group"), 
		csAppFolder + CString("\\Media\\DataCreator\\Group.htm"));
	pState->AddInvokeShell(CString("add_group"), OnAddGroup, (DWORD)this);
	pState->AddInvokeShell(CString("add_data_items"), OnAddDataItems, (DWORD)this);
	pState->AddInvokeShell(CString("edit_group_name"), OnChangeGroupName, (DWORD)this);
	pState->SetGetPropertyCallback(GetPropertyCollection, (DWORD)this);

	pState = mCollectionProperties.AddState(CString("DataItem"), 
		csAppFolder + CString("\\Media\\DataCreator\\DataItem.htm"));
	pState->SetGetPropertyCallback(GetPropertyCollection, (DWORD)this);
}

void CDataCollectionsDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CDataCollectionsDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CDataCollectionsDlg::InitializeCollectionSolution()
{
	ItemDataStruct* pItemData = new ItemDataStruct;
	pItemData->dwItemData = (DWORD)this;
	pItemData->Select = OnSelectIntro;
	pItemData->lClk = OnSelectIntro;
	HTREEITEM htiCurrent = mCollectionTree.InsertActiveItem(_T("Intro"), pItemData);

	pItemData = new ItemDataStruct;
	pItemData->dwItemData = (DWORD)this;
	pItemData->Select = OnSelectOperations;
	pItemData->lClk = OnSelectOperations;
	mCollectionTree.InsertActiveItem(_T("Collection Operations"), pItemData);

	htiCollectionRoot = mCollectionTree.InsertItem(_T("No collections avaliable"));

	pItemData = new ItemDataStruct;
	pItemData->dwItemData = (DWORD)this;
	pItemData->Select = OnSelectAbout;
	pItemData->lClk = OnSelectAbout;
	mCollectionTree.InsertActiveItem(_T("About"), pItemData);
}

void CDataCollectionsDlg::ReleaseControls()
{

}

// Formating output(solution)
CString CDataCollectionsDlg::PrepareCollectionName(CString& Name)
{
	return CString("[") + Name + CString("] Collection");
}
CString CDataCollectionsDlg::PrepareGroupName(CString& Name)
{
	return CString("[") + Name + CString("] Group");
}

// Building solution structure
void CDataCollectionsDlg::ShowCollection()
{
	ItemDataStruct* pItemData = new ItemDataStruct;
	pItemData->dwItemData = (DWORD)this;
	pItemData->Select = OnSelectCollection;
	pItemData->lClk = OnSelectCollection;

	mCollectionTree.SetItemText(htiCollectionRoot, 
		PrepareCollectionName(mDataCollection.GetCollectionName()));
	mCollectionTree.SetItemData(htiCollectionRoot, (DWORD_PTR)pItemData);
	mCollectionTree.SetItemState(htiCollectionRoot, TVIS_BOLD, TVIS_BOLD);

	CreateGroup(htiCollectionRoot, mDataCollection.GetCollectionGroup());

	mCollectionProperties.ShowState(CString("Collection"));
}

void CDataCollectionsDlg::CreateGroup(HTREEITEM htiParent, CCollectionGroup* pGroup)
{	
	CGroupItemParam* pGroupItemParam = new CGroupItemParam(this, pGroup);

	ItemDataStruct* pItemData = new ItemDataStruct;
	pItemData->dwItemData = (DWORD)pGroupItemParam;
	pItemData->Select = OnSelectGroupItem;
	pItemData->lClk = OnSelectGroupItem;
	pItemData->State = TVIS_BOLD;
	pGroupItemParam->htiGroup = mCollectionTree.InsertActiveItem(
		PrepareGroupName(pGroup->GetGroupName()), pItemData, htiParent);
	
	pGroup->SetAppSpecData((DWORD)pGroupItemParam);

	pGroupItemParam->htiSubgroupsRoot = mCollectionTree.InsertItem(
		_T("Groups"), pGroupItemParam->htiGroup);
	pGroupItemParam->htiDataArrayRoot = mCollectionTree.InsertItem(
		_T("Data Array"), pGroupItemParam->htiGroup);

	mCollectionTree.Expand(htiParent, TVE_EXPAND);
	mCollectionTree.Expand(pGroupItemParam->htiGroup, TVE_EXPAND);

	// Add subgroups 
	pGroup->CreateEnumerator();
	while (CCollectionGroup* pCurGroup = pGroup->GetNextGroup())
		CreateGroup(pGroupItemParam->htiSubgroupsRoot, pCurGroup);

	// Add data items
	pGroup->GetDataArray()->CreateEnumerator();
	while (CCollectionDataItem* pDataItem = pGroup->GetDataArray()->GetNextItem())
		AddDataItem(pGroupItemParam->htiDataArrayRoot, pDataItem);
}

void CDataCollectionsDlg::AddDataItem(HTREEITEM htiParent, CCollectionDataItem* pItem)
{
	CDataItemParam* pDataItemParam = new CDataItemParam(this, pItem);

	ItemDataStruct* pItemData = new ItemDataStruct;
	pItemData->dwItemData = (DWORD)pDataItemParam;
	pItemData->Select = OnSelectDataItem;
	pItemData->lClk = OnSelectDataItem;
	pDataItemParam->htiItem = mCollectionTree.InsertActiveItem(
		pItem->GetFileName(), pItemData, htiParent);
	
	pItem->SetAppSpecData((DWORD)pDataItemParam);
}