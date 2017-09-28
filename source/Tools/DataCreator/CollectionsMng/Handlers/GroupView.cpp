#include "stdafx.h"
#include "../../DataCreator.h"
#include "GroupView.h"

#include "../../DataCollectionsDlg.h"
#include "../NewGroupDlg.h"

// Group View Operation Handlers
void OnAddGroup(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;	

	CNewGroupDlg mDlg;
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		CCollectionGroup* pGroup = pDlg->pCurrentGroup->AddGroup(mDlg.mGroupName);

		CGroupItemParam* pGroupParam = (CGroupItemParam*)pDlg->pCurrentGroup->GetAppSpecData();

		pDlg->CreateGroup(pGroupParam->htiSubgroupsRoot, pGroup);

		pDlg->mCollectionProperties.UpdateState();
	} else
		pDlg->mCollectionProperties.UpdateState();
}

void OnChangeGroupName(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	CNewGroupDlg mNewGroupDlg;
	mNewGroupDlg.mGroupName = pDlg->pCurrentGroup->GetGroupName();
	mNewGroupDlg.mWmdTitle = _T("Edit Group Name");
	int res = mNewGroupDlg.DoModal();
	if (res == IDOK)
	{
		pDlg->pCurrentGroup->SetGroupName(mNewGroupDlg.mGroupName);

		CGroupItemParam* pGroupItemParam = 
			(CGroupItemParam*)pDlg->pCurrentGroup->GetAppSpecData();

		pDlg->mCollectionTree.SetItemText(pGroupItemParam->htiGroup, 
			pDlg->PrepareGroupName(mNewGroupDlg.mGroupName));
	}
	
	pDlg->mCollectionProperties.UpdateState();
}

void OnAddDataItems(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;
	CGroupItemParam* pGroupItemParam = (CGroupItemParam*)pDlg->pCurrentGroup->GetAppSpecData();

	CFileDialog	mFileDlg(true, "", "", OFN_ALLOWMULTISELECT, "Image Files|*.*||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		for (POSITION pos = mFileDlg.GetStartPosition();pos;)
		{
			CCollectionDataItem* pItem = pDlg->pCurrentGroup->GetDataArray()->AddDataItem(
				mFileDlg.GetNextPathName(pos));

			pDlg->AddDataItem(pGroupItemParam->htiDataArrayRoot, pItem);
		}
				
		pDlg->mCollectionProperties.UpdateState();

		pDlg->mCollectionTree.Invalidate();
	} else
		pDlg->mCollectionProperties.UpdateState();
}