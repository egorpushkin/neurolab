#pragma once

#include "../CmnDataCollection.h"
#include "../System/Directory.h"

class CDataCollectionOperation_Save
{
public:
	static bool SaveCollection(		 
		IDataCollection* pCollection,
		CString& FileName,
		IXMLDOMDocument* pXMLDom)
	{
		CString csRootXML = CString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \
			<Collection name=\"") + 
			pCollection->GetCollectionName() +
			CString("\"></Collection>");
		CComBSTR bstrRootXML(csRootXML);

		// Creating xml core structure
		VARIANT_BOOL bvResult; 
		HRESULT hr = pXMLDom->loadXML(bstrRootXML, &bvResult);
		if (FAILED(hr)) 
			return false;
		if (bvResult == VARIANT_FALSE)
			return false;
		
		IXMLDOMElement* pXMLElement = NULL;
		hr = pXMLDom->get_documentElement(&pXMLElement);
		if (FAILED(hr)) 
			return false;

		// Adding xml content
		bool bRet = AddGroup(pCollection->GetCollectionGroup(), 
			FileName, pXMLElement, pXMLDom);

		pXMLElement->Release();        			
	
		return bRet;
	}

	static bool AddGroup(
		CCollectionGroup* pGroup, 
		CString& FileName,
		IXMLDOMElement* pXMLElement, 
		IXMLDOMDocument* pXMLDom)
	{
		// Creating Group node
		IXMLDOMNode* pXMLGroupNode = CCommonXML::CreateParentNode(
			CString("Group"), pXMLElement, pXMLDom);
		if (!pXMLGroupNode)
			return false;

		// Adding Name attribute
		if (!CCommonXML::AddAttribute(CString("name"), 
			pGroup->GetGroupName(), pXMLGroupNode, pXMLDom))
		{
			pXMLGroupNode->Release();

			return false;
		}
	
		// Adding subgroups
		IXMLDOMElement* pXMLGroupElement = NULL;
		HRESULT hr = pXMLGroupNode->QueryInterface(IID_IXMLDOMElement, (void**)&pXMLGroupElement);
		if (FAILED(hr) || !pXMLGroupElement)
		{
			pXMLGroupNode->Release();

			return false;
		}

		pGroup->CreateEnumerator();
		while (CCollectionGroup* pCurGroup = pGroup->GetNextGroup())
		{
			bool bRet = AddGroup(pCurGroup, FileName, pXMLGroupElement, pXMLDom);
			if (!bRet)
			{
				pXMLGroupNode->Release();
				pXMLGroupElement->Release();

				return false;
			}
		}

		pXMLGroupElement->Release();

		// Adding Data Array Items
		IXMLDOMNode* pXMLDataArrayNode = CCommonXML::CreateParentNode(
			CString("DataArray"), pXMLGroupNode, pXMLDom);
		if (!pXMLDataArrayNode)
		{
			pXMLGroupNode->Release();
		
			return false;
		}

		// Adding Data Array Items
		pGroup->GetDataArray()->CreateEnumerator();
		while (CCollectionDataItem* pDataItem = pGroup->GetDataArray()->GetNextItem())
		{
			// Adding Data Item Node
			IXMLDOMNode* pXMLDataItemNode = CCommonXML::CreateParentNode(
				CString("DataItem"), pXMLDataArrayNode, pXMLDom);
			if (!pXMLDataItemNode)
			{
				pXMLDataArrayNode->Release();
				pXMLGroupNode->Release();
			
				return false;
			}

			// Adding filename attribute
			CString csRelativeFileName = CPath::GetRelativePath(FileName, pDataItem->GetFileName());

			if (!CCommonXML::AddAttribute(CString("filename"), 
				csRelativeFileName, pXMLDataItemNode, pXMLDom))
			{
				pXMLDataItemNode->Release();				
				pXMLDataArrayNode->Release();
				pXMLGroupNode->Release();

				return false;
			}            	
		}

		pXMLDataArrayNode->Release();
		pXMLGroupNode->Release();

		return true;
	}
};