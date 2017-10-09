#pragma once

#include "CmnXML.h"
#include "CmnDataFile.h"
#include "DataCollection/DataCollection.h"
#include "System/Directory.h"

class CConverterItem
{
public:
	CConverterItem()
		: csCollectionGroupName(_T(""))
		, iDataSymbol(-1)
	{}

	CConverterItem(CString GroupName, int Symbol)
		: csCollectionGroupName(GroupName)
		, iDataSymbol(Symbol)
	{}

	CString			csCollectionGroupName;
	int				iDataSymbol;
};

class CCollectionConverter
{
public:
	CCollectionConverter()
		: bIsCreated(false)
		, csProjectName(_T(""))
		, csDataFileName(_T(""))
		, csDataCollectionFileName(_T(""))
	{}

	~CCollectionConverter()
	{
		ReleaseProject();
	}

	bool CreateProject(
		CString& ProjectName, 
		CString& DataFileName, 
		CString& DataCollectionName)
	{
		ReleaseProject();
		
		SetProjectName(ProjectName);

		csDataFileName = DataFileName;
		csDataCollectionFileName = DataCollectionName;

		if (!mDataFile.LoadFile(csDataFileName))
		{
			ClearProjectStrings();
			return false;
		}

		if (!mDataCollection.LoadCollection(csDataCollectionFileName))
		{
			mDataFile.FreeLoadedData();
			
			ClearProjectStrings();
			return false;		 
		}

		bIsCreated = true;
		return true;
	}

	void ReleaseProject()
	{
		if (bIsCreated)
		{
			ClearProjectStrings();

            RELEASE_LIST(mConverterItems, CConverterItem*, true)

			mDataFile.FreeLoadedData();
			mDataCollection.DestructCollection();

			bIsCreated = false;
		}		
	}

	void ClearProjectStrings()
	{
		csProjectName = _T("");
		csDataFileName = _T("");
		csDataCollectionFileName = _T("");
	}

	bool IsDataPrepared()
	{
		if (mDataFile.IsLoaded() && mDataCollection.IsCreated())
			return true;

		return false;
	}

	CDataFile* GetDataFile()
	{
		return &mDataFile;
	}

	CDataCollection* GetDataCollection()	
	{	
		return &mDataCollection;
	}

	bool IsCreated()
	{
		return bIsCreated;
	}

	CString GetProjectName()
	{
		return csProjectName;
	}

	void SetProjectName(CString& ProjectName)
	{
		csProjectName = ProjectName;
	}

	CConverterItem* AddConverterItem(CString GroupName, int Symbol)
	{
		CConverterItem* pItem = new CConverterItem(GroupName, Symbol);
	
		mConverterItems.AddTail(pItem);

		return pItem;
	}

	virtual bool SaveProject(CString& FileName)
	{
		CCommonXML tmXMLObject(FileName);
		tmXMLObject.CreateInstance();

		csProjectFileName = FileName;

		if (Serialize(tmXMLObject.GetXMLDOMInstance(), false))
			if (tmXMLObject.SaveFile())
				return true;

		return false;
	}

	virtual bool LoadProject(CString& FileName)
	{
		ReleaseProject();

		CCommonXML tmXMLObject(FileName);
		tmXMLObject.CreateInstance();

		csProjectFileName = FileName;

		if (tmXMLObject.LoadFile())
			if (Serialize(tmXMLObject.GetXMLDOMInstance(), true))
			{
				bIsCreated = true; 

				return true;
			}
	
		return false;
	}    

	// IXMLStorageController implementations section
	virtual bool Serialize(IXMLDOMDocument* pXMLDom, bool bIsLoad)
	{
		if (bIsLoad)
		{
			IXMLDOMElement* pXMLElement = NULL;
			HRESULT hr = pXMLDom->get_documentElement(&pXMLElement);
			if (FAILED(hr)) 
				return false;

			USES_CONVERSION;

			CComBSTR bstrRootName;
			pXMLElement->get_baseName(&bstrRootName);
			
			if (CString(W2T(bstrRootName)) != CString("CollectionConverter"))
			{
				pXMLElement->Release();

				return false;
			}	

			CString csRelativeDataFileName;
			CString csRelativeCollectionFileName;

			CCommonXML::GetAttributeValue(CString("name"), 
				pXMLElement, csProjectName);
			CCommonXML::GetAttributeValue(CString("datafilename"), 
				pXMLElement, csRelativeDataFileName);
			CCommonXML::GetAttributeValue(CString("collectionfilename"), 
				pXMLElement, csRelativeCollectionFileName);

			csDataFileName = CPath::RestoreFullName(
				csProjectFileName, csRelativeDataFileName);
			csDataCollectionFileName = CPath::RestoreFullName(
				csProjectFileName, csRelativeCollectionFileName);

			pXMLElement->Release();

			if (!mDataFile.LoadFile(csDataFileName))
				return false;

			if (!mDataCollection.LoadCollection(csDataCollectionFileName))
				return false;				

			IXMLDOMNodeList* pXMLNodeList = NULL;
			hr = pXMLDom->getElementsByTagName(CComBSTR("Item"), &pXMLNodeList);
			if (FAILED(hr))
				return false;

            long lCount;
			hr = pXMLNodeList->get_length(&lCount);
			if (FAILED(hr))
			{
				pXMLNodeList->Release();

				return false;
			}

			for (long i = 0;i < lCount;i++)
			{				
				IXMLDOMNode* pXMLItemNode = NULL;
				hr = pXMLNodeList->get_item(i, &pXMLItemNode);
				if (FAILED(hr))
				{
					pXMLNodeList->Release();

					return false;				
				}

				CString csGroupName;
				CString csSymbol;

				CCommonXML::GetAttributeValue(CString("groupname"), 
					pXMLItemNode, csGroupName);
				CCommonXML::GetAttributeValue(CString("symbol"), 
					pXMLItemNode, csSymbol);

                int iSymbol = atoi(csSymbol);

				AddConverterItem(csGroupName, iSymbol);		
			
				pXMLItemNode->Release();
			}

			pXMLNodeList->Release();

			return true;
		} else
		{
			CString csRelativeDataFileName = CPath::GetRelativePath(
				csProjectFileName, csDataFileName);
			CString csRelativeCollectionFileName = CPath::GetRelativePath(
				csProjectFileName, csDataCollectionFileName);

			CString csRootXML = CString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \
				<CollectionConverter name=\"") + 
				GetProjectName() +
				CString("\" datafilename=\"") + 
				csRelativeDataFileName + 
				CString("\" collectionfilename=\"") + 
				csRelativeCollectionFileName +
				CString("\"></CollectionConverter>");
			CComBSTR bstrRootXML(csRootXML);

			// Creating xml core structure
			VARIANT_BOOL bvResult; 
			HRESULT hr = pXMLDom->loadXML(bstrRootXML, &bvResult);
			if (FAILED(hr)) 
				return false;
			if (bvResult == VARIANT_FALSE)
				return false;	

			// Receiving root xml element 
			IXMLDOMElement* pXMLElement = NULL;
			hr = pXMLDom->get_documentElement(&pXMLElement);
			if (FAILED(hr)) 
				return false;

			// Adding Items node
			IXMLDOMNode* pXMLItemsNode = CCommonXML::CreateParentNode(
				CString("Items"), pXMLElement, pXMLDom);
			if (!pXMLItemsNode)
			{
				pXMLElement->Release();

				return false;
			}

			pXMLElement->Release();

			// Adding converter items 
			for(POSITION pos = mConverterItems.GetHeadPosition();pos;)
			{
				CConverterItem* pItem = mConverterItems.GetNext(pos);
				
				IXMLDOMNode* pXMLItemNode = CCommonXML::CreateParentNode(
					CString("Item"), pXMLItemsNode, pXMLDom);
				if (!pXMLItemNode)
				{
					pXMLItemsNode->Release();

					return false;
				}

				if (!CCommonXML::AddAttribute(CString("groupname"), 
					pItem->csCollectionGroupName, pXMLItemNode, pXMLDom))
				{
					pXMLItemsNode->Release();

					return false;
				}

                CString tmSymbol;
				tmSymbol.Format("%d", pItem->iDataSymbol);

				if (!CCommonXML::AddAttribute(CString("symbol"), 
					tmSymbol, pXMLItemNode, pXMLDom))
				{
					pXMLItemsNode->Release();

					return false;
				}

				pXMLItemNode->Release();
			}

			pXMLItemsNode->Release();

			return true;
		}
	}

	ENUMERATOR(mConverterItems, CConverterItem*, CreateEnumerator, GetNextItem, posItems)

	int GetItemsCount()
	{
		return mConverterItems.GetCount();
	}

private:
	
	CDataFile			mDataFile;
	CDataCollection		mDataCollection;

	CString				csDataFileName;
	CString				csDataCollectionFileName;

	bool				bIsCreated;

	CString				csProjectName;

	CList<CConverterItem*, CConverterItem*> mConverterItems;

	// Temporary properties
	CString				csProjectFileName;
};