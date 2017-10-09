#include "stdafx.h"
#include "../../DataCreator.h"
#include "ExternalProperties.h"

#include "../../DataCollectionsDlg.h"

// Callback External Handlers
CString GetPropertyCollection(CString& PropertyName, DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	if (PropertyName == CString(_T("CollectionName")))
		return pDlg->mDataCollection.GetCollectionName();

	if (PropertyName == CString(_T("GroupName")))
		if (pDlg->pCurrentGroup)
			return pDlg->pCurrentGroup->GetGroupName();

	if (PropertyName == CString(_T("CollectionFileName")))
		return pDlg->csFileName;

	if (PropertyName == CString(_T("GlobalSubgroupsCount")))
	{
		CString tmGroupsCount;
		tmGroupsCount.Format("%d", 
			pDlg->mDataCollection.GetCollectionGroup()->GetGroupsCount());

		return tmGroupsCount;
	}

	if (PropertyName == CString(_T("GlobalTotalDataObjects")))
	{
		CString tmItemsCount;
		tmItemsCount.Format("%d", 
			pDlg->mDataCollection.GetCollectionGroup()->GetDataArray()->GetItemsCount());

		return tmItemsCount;
	}

	if (PropertyName == CString(_T("SubgroupsCount")))
		if (pDlg->pCurrentGroup)
		{
			CString tmGroupsCount;
			tmGroupsCount.Format("%d", pDlg->pCurrentGroup->GetGroupsCount());

			return tmGroupsCount;
		}

	if (PropertyName == CString(_T("TotalDataObjects")))
		if (pDlg->pCurrentGroup)
		{
			CString tmItemsCount;
			tmItemsCount.Format("%d", pDlg->pCurrentGroup->GetDataArray()->GetItemsCount());

			return tmItemsCount;
		}

	if (PropertyName == CString(_T("DataItemFileName")))
		if (pDlg->pCurrentDataItem)
			return pDlg->pCurrentDataItem->GetFileName();

	return _T("");
}
