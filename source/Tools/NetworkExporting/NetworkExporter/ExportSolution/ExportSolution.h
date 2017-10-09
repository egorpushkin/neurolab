#pragma once

#include "Templates\Enumerator.h"
#include "CmnObjects.h"

#include "SolutionSerialize.h"

class CExportItem : public IObject
{
public:
	CString			csItemName;
	CString			csItemType;
	CString			csItemVersion;
	CString			csItemPathPrefix;
	CString			csItemDescription;

	virtual CString GetClassString()
	{
        return _T("CExportItem");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
	}
};

class CExportGroup : public IObject
{
public:
	~CExportGroup()
	{
		RELEASE_LIST(mItems, CExportItem*, true)
	}

	void AddItem(CExportItem* pExportItem)
	{	
		mItems.AddTail(pExportItem);
	}

	CString			csGroupName;
	CString			csGroupFolder;

	CExportItem* GetHeadItem()
	{
		return mItems.GetHead();
	}

	ENUMERATOR(mItems, CExportItem*, CreateEnumerator, GetNextItem, posItemsList)

	virtual CString GetClassString()
	{
        return _T("CExportGroup");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
	}
private:
	CList<CExportItem*, CExportItem*> mItems;
};

class CExportSolution
{
public:
	~CExportSolution()
	{
		RELEASE_LIST(mGroups, CExportGroup*, true)
	}

	bool LoadSolution();
	bool VerifySolution();

	void AddGroup(CExportGroup* pExportGroup)
	{	
		mGroups.AddTail(pExportGroup);
	}

	void SetProjectFileName(CString& FileName)
	{
		CExportGroup* pGroup = GetGroupByName(CString(_T("Project Files")));	
		if (pGroup)
		{
			CExportItem* pItem = pGroup->GetHeadItem();
			if (pItem)
				pItem->csItemName = FileName;
		}
	}

	CExportGroup* GetGroupByName(CString& GroupName)
	{
		for (POSITION pos = mGroups.GetHeadPosition();pos;)
		{
			CExportGroup* pGroup = mGroups.GetNext(pos);		
			if (pGroup->csGroupName == GroupName)
				return pGroup;
		}

        return NULL;	
	}

	CString			csAppFolder;

	ENUMERATOR(mGroups, CExportGroup*, CreateEnumerator, GetNextGroup, posGroupsList)

private:
	CList<CExportGroup*, CExportGroup*> mGroups;

};