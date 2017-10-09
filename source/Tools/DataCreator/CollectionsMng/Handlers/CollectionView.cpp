#include "stdafx.h"
#include "../../DataCreator.h"
#include "CollectionView.h"

#include "../../DataCollectionsDlg.h"
#include "../NewCollectionDlg.h"

// Collection View Operation Handlers
void OnChangeCollectionName(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	CNewCollectionDlg mNewCollDlg;
	mNewCollDlg.mCollectionName = pDlg->mDataCollection.GetCollectionName();
	mNewCollDlg.mWmdTitle = _T("Edit Collection Name");
	int res = mNewCollDlg.DoModal();
	if (res == IDOK)
	{
		pDlg->mDataCollection.SetCollectionName(mNewCollDlg.mCollectionName);
		pDlg->mCollectionTree.SetItemText(pDlg->htiCollectionRoot, 
			pDlg->PrepareCollectionName(mNewCollDlg.mCollectionName));
	}
	
	pDlg->mCollectionProperties.UpdateState();
}

void OnShowCollectionGlobalGroup(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	// Update current temporary properties 
	pDlg->pCurrentGroup = pDlg->mDataCollection.GetCollectionGroup();
	pDlg->pCurrentDataItem = NULL;
	
	pDlg->mCollectionProperties.ShowState(CString("Group"));
}