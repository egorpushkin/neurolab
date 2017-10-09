#include "stdafx.h"
#include "../../DataCreator.h"
#include "SolutionSpecific.h"

#include "../../DataCollectionsDlg.h"

// Solution Control Specific Callback Command Handlers
void OnSelectGroupItem(DWORD Param)
{
	IParDef(pItemData, pData, Param, CGroupItemParam*)

	// Update current temporary properties 
	pData->pMainDialog->pCurrentGroup = pData->pOwnerGroup;
	pData->pMainDialog->pCurrentDataItem = NULL;
	
	pData->pMainDialog->mCollectionProperties.ShowState(CString("Group"));	
}

void OnSelectDataItem(DWORD Param)
{
	IParDef(pItemData, pData, Param, CDataItemParam*)

	// Update current temporary properties 
	pData->pMainDialog->pCurrentGroup = pData->pOwnerItem->GetOwnerGroup();
	pData->pMainDialog->pCurrentDataItem = pData->pOwnerItem;
	
	pData->pMainDialog->mCollectionProperties.ShowState(CString("DataItem"));		

}
