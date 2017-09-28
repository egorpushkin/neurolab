#pragma once

#include "../Templates/Enumerator.h"
class CCollectionGroup;

class CCollectionDataItem
{
public:
	CCollectionDataItem()
		: csFileName(_T(""))
		, pOwnerGroup(NULL)
	{
	}

	CCollectionDataItem(CString& FileName)	
		: csFileName(FileName)
		, pOwnerGroup(NULL)
	{
	}

	CCollectionDataItem(CString& FileName, CCollectionGroup* pGroup)	
		: csFileName(FileName)
		, pOwnerGroup(pGroup)
	{
	}

	~CCollectionDataItem()
	{
	}

	CString GetFileName()
	{
		return csFileName;
	}

	void SetAppSpecData(DWORD Data)
	{	
		dwData = Data;
	}

	DWORD GetAppSpecData()
	{
		return dwData;	
	}

	void SetOwnerGroup(CCollectionGroup* pGroup)
	{
		pOwnerGroup = pGroup;
	}

	CCollectionGroup* GetOwnerGroup()
	{
		return pOwnerGroup;
	}

private:
	// Relative file name of data item
	CString			csFileName;

	// Application specific data
	DWORD			dwData;

	// Owner group
	CCollectionGroup* pOwnerGroup;
};

class CCollectionDataArray
{
public:
	CCollectionDataArray()
		: pOwnerGroup(NULL)
	{
	}
	~CCollectionDataArray()
	{
		ReleaseDataItems();
	}

	ENUMERATOR(mDataItems, CCollectionDataItem*, CreateEnumerator, GetNextItem, posDataItems)

	int GetItemsCount()
	{
		return mDataItems.GetCount();
	}

	void SetAppSpecData(DWORD Data)
	{	
		dwData = Data;
	}

	DWORD GetAppSpecData()
	{
		return dwData;	
	}

	void SetOwnerGroup(CCollectionGroup* pGroup)
	{
		pOwnerGroup = pGroup;
	}

	CCollectionGroup* GetOwnerGroup()
	{
		return pOwnerGroup;
	}

	// Managing data content
	CCollectionDataItem* AddDataItem(CString& FileName)
	{
		CCollectionDataItem* pDataItem = new CCollectionDataItem(FileName, pOwnerGroup);

		mDataItems.AddTail(pDataItem);

        return pDataItem;
	}

	void DestructDataArray()
	{
		ReleaseDataItems();
	}

private:
	void ReleaseDataItems()
	{	
		RELEASE_LIST(mDataItems, CCollectionDataItem*, true)
	}

private:
	// Data array items
	CList<CCollectionDataItem*, CCollectionDataItem*> mDataItems;

	// Application specific data
	DWORD			dwData;

	// Owner group
	CCollectionGroup* pOwnerGroup;
};