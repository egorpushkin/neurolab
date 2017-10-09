#pragma once

#include "interface_idds.h"

#include "../CmnXML.h"
#include "../CmnDataCollection.h"

#include "Operation_Save.h"
#include "Operation_Load.h"

class CDataCollection : 
	public IDataCollection,
	public IXMLStorageController
{
public:
	CDataCollection()
		: bIsCreated(false)
	{}   
	
	~CDataCollection()
	{
		DestructCollection();
	}

	// IDataCollection implementations section
	// state founctions
	virtual bool IsCreated()
	{
		return bIsCreated;
	}

	// creation/destruction functions
	virtual void CreateCollection(CString& csName)
	{
		DestructCollection();

		csCollectionName = csName;
		
		bIsCreated = true;
	}

	virtual void DestructCollection()
	{
		if (bIsCreated)
		{
			mCollectionGroup.DestructGroup();
	
			bIsCreated = false;
		}	
	}

	// properties
	virtual CString GetCollectionName()
	{
		return csCollectionName;
	}

	virtual void SetCollectionName(CString& Name)
	{
		csCollectionName = Name;
	}

	virtual CCollectionGroup* GetCollectionGroup()
	{
		return &mCollectionGroup;
	}

	virtual CCollectionGroup* GetGroupByName(CString& Name)
	{
		return mCollectionGroup.GetGroupByName(Name);
	}

	// Save/Load operations
	virtual bool LoadCollection(CString& FileName)
	{
		CCommonXML tmXMLObject(FileName);
		tmXMLObject.CreateInstance();

		csCollectionFileName = FileName;

		if (tmXMLObject.LoadFile())
			if (Serialize(tmXMLObject.GetXMLDOMInstance(), true))
			{
				bIsCreated = true; 

				return true;
			}
	
		return false;
	}

	virtual bool SaveCollection(CString& FileName)
	{
		CCommonXML tmXMLObject(FileName);
		tmXMLObject.CreateInstance();
		
		csCollectionFileName = FileName;

		if (Serialize(tmXMLObject.GetXMLDOMInstance(), false))
			if (tmXMLObject.SaveFile())
				return true;

		return false;
	}

	// IXMLStorageController implementations section
	virtual bool Serialize(IXMLDOMDocument* pXMLDom, bool bIsLoad)
	{
		if (bIsLoad)
		{
			return CDataCollectionOperation_Load::LoadCollection(this, csCollectionFileName, pXMLDom);		
		} else
		{
			return CDataCollectionOperation_Save::SaveCollection(this, csCollectionFileName, pXMLDom);
		}
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CDataCollection");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IDataCollection:
			*ppvObject = (IDataCollection*)this;
			break;
		case IDD_IXMLStorageController:
			*ppvObject = (IXMLStorageController*)this;
			break;
		}
	}

private:

	bool				bIsCreated;
	
	CString				csCollectionName;

	CCollectionGroup	mCollectionGroup;

	// Temporary properties
	CString				csCollectionFileName;
};
