#pragma once

#include "../DataCreator.h"

#include "../DataCollectionsDlg.h"

class CGroupItemParam
{
public:
	CGroupItemParam(CDataCollectionsDlg* pDlg, CCollectionGroup* pGroup)
		: pMainDialog(pDlg)
		, pOwnerGroup(pGroup)
	{		
	}

	CDataCollectionsDlg*	pMainDialog;
	CCollectionGroup*		pOwnerGroup;	

	HTREEITEM				htiGroup;
	HTREEITEM				htiSubgroupsRoot;
	HTREEITEM				htiDataArrayRoot;
};

class CDataItemParam
{
public:
	CDataItemParam(CDataCollectionsDlg* pDlg, CCollectionDataItem* pItem)
		: pMainDialog(pDlg)
		, pOwnerItem(pItem)
	{		
	}

	HTREEITEM				htiItem;

	CDataCollectionsDlg*	pMainDialog;
	CCollectionDataItem*	pOwnerItem;	
};