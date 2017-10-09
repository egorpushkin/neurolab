#pragma once

#include "../Templates/Enumerator.h"
#include "CollectionDataArray.h"

class CCollectionGroup
{
public:
	CCollectionGroup()
		: pParentGroup(NULL)
	{
		mDataArray.SetOwnerGroup(this);
	}

	CCollectionGroup(CString& Name)
		: pParentGroup(NULL)
		, csGroupName(Name)
	{
		mDataArray.SetOwnerGroup(this);
	}

	CCollectionGroup(CString& Name, CCollectionGroup* pGroup)
		: csGroupName(Name)
		, pParentGroup(pGroup)
	{
		mDataArray.SetOwnerGroup(this);
	}

	~CCollectionGroup()
	{}

	void SetGroupName(CString& Name)
	{
		csGroupName = Name;
	}

	CString GetGroupName()
	{
		return csGroupName;
	}

	void SetAppSpecData(DWORD Data)
	{	
		dwData = Data;
	}

	DWORD GetAppSpecData()
	{
		return dwData;	
	}

	ENUMERATOR(mSubgroups, CCollectionGroup*, CreateEnumerator, GetNextGroup, posGroups)

	int GetGroupsCount()
	{
		return mSubgroups.GetCount();
	}

	void SetParentGroup(CCollectionGroup* pGroup)
	{
		pParentGroup = pGroup;
	}

	CCollectionGroup* GetParentGroup()
	{
		return pParentGroup;
	}

	CCollectionDataArray* GetDataArray()
	{
		return &mDataArray;
	}

	// Managing data content
	CCollectionGroup* AddGroup(CString& GroupName)
	{
        CCollectionGroup* pGroup = new CCollectionGroup(GroupName, this);

		mSubgroups.AddTail(pGroup);

        return pGroup;
	}

	void DestructGroup()
	{
		RELEASE_LIST(mSubgroups, CCollectionGroup*, true); 

		mDataArray.DestructDataArray();
	}

	CCollectionGroup* GetGroupByName(CString& Name)
	{
		if (Name == csGroupName)
			return this;

		for(POSITION pos = mSubgroups.GetHeadPosition();pos;)
		{
			CCollectionGroup* pGroup = mSubgroups.GetNext(pos);

			CCollectionGroup* pFoundGroup = pGroup->GetGroupByName(Name);
			if (pFoundGroup)		
				return pFoundGroup;
		}

		return NULL;
	}

private:

	CString			csGroupName;

	// Subgroups list
	CList<CCollectionGroup*, CCollectionGroup*> mSubgroups;
	
	// Group data array
	CCollectionDataArray mDataArray;

	// Application specific data
	DWORD			dwData;

	// Parent group
	CCollectionGroup* pParentGroup;
};
