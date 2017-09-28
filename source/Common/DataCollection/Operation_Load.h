#pragma once

#include "../CmnDataCollection.h"
#include "../System/Directory.h"

class CDataCollectionOperation_Load
{
public:
	static bool LoadCollection(		 
		IDataCollection* pCollection,
		CString& FileName,
		IXMLDOMDocument* pXMLDom)
	{
		IXMLDOMElement* pXMLElement = NULL;
		HRESULT hr = pXMLDom->get_documentElement(&pXMLElement);
		if (FAILED(hr)) 
			return false;

		USES_CONVERSION;

		CComBSTR bstrRootName;
		pXMLElement->get_baseName(&bstrRootName);
		
		if (CString(W2T(bstrRootName)) != CString("Collection"))
		{
			pXMLElement->Release();

			return false;
		}

		IXMLDOMNamedNodeMap* pXMLNamedNodeMap = NULL;
		hr = pXMLElement->get_attributes(&pXMLNamedNodeMap);
        if (FAILED(hr))
		{
			pXMLElement->Release();
		
			return false;
		}

		IXMLDOMNode* pXMLAttrNode = NULL;
		hr = pXMLNamedNodeMap->getNamedItem(CComBSTR("name"), &pXMLAttrNode);
		if (FAILED(hr))
		{
			pXMLElement->Release();
			pXMLNamedNodeMap->Release();
		
			return false;
		}

		IXMLDOMAttribute* pXMLAttribute = NULL;
		hr = pXMLAttrNode->QueryInterface(IID_IXMLDOMAttribute, (void**)&pXMLAttribute);
		if (FAILED(hr))
		{
			pXMLElement->Release();
			pXMLNamedNodeMap->Release();
			pXMLAttrNode->Release();
		
			return false;		
		}

		VARIANT varCollectionName;
		pXMLAttribute->get_value(&varCollectionName);
		
		pXMLAttribute->Release();
		pXMLAttrNode->Release();
		pXMLNamedNodeMap->Release();

		pCollection->CreateCollection(CString(W2T(varCollectionName.bstrVal)));

		IXMLDOMNodeList* pXMLNodeList = NULL;
		hr = pXMLElement->get_childNodes(&pXMLNodeList);
        if (FAILED(hr))
		{
			pXMLElement->Release();

			return false; 
		}

		pXMLElement->Release();

		long lCount;		
		hr = pXMLNodeList->get_length(&lCount);
		if (FAILED(hr) || lCount != 1)
		{			
			pXMLNodeList->Release();
		
			return false;
		}

		IXMLDOMNode* pXMLRootGroup = NULL;
		hr = pXMLNodeList->get_item(0, &pXMLRootGroup);
		if (FAILED(hr))
		{
			pXMLNodeList->Release();

			return false;
		}

		pXMLNodeList->Release();

		CString csGroupName;
		CCommonXML::GetAttributeValue(CString("name"), pXMLRootGroup, csGroupName);

		pCollection->GetCollectionGroup()->SetGroupName(csGroupName);

		bool bRet = AddContentToGroup(pCollection->GetCollectionGroup(), 
			FileName, pXMLRootGroup);

		pXMLRootGroup->Release();
	
		return true;
	}

	static bool AddContentToGroup(
		CCollectionGroup* pGroup,
		CString& FileName,
		IXMLDOMNode* pXMLGroup)
	{
		IXMLDOMNodeList* pXMLNodeList = NULL;
		HRESULT hr = pXMLGroup->get_childNodes(&pXMLNodeList);
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
			IXMLDOMNode* pXMLNode = NULL;
			hr = pXMLNodeList->get_item(i, &pXMLNode);
			if (FAILED(hr))
			{
				pXMLNodeList->Release();

				return false;
			}			

			CComBSTR bstrNodeName;
			pXMLNode->get_baseName(&bstrNodeName);

			USES_CONVERSION;

			CString csNodeName(W2T(bstrNodeName));
			if (csNodeName == CString("DataArray"))
			{	
				bool bRet = FillDataArray(pGroup->GetDataArray(), FileName, pXMLNode);
				if (!bRet)
				{
					pXMLNodeList->Release();
					pXMLNode->Release();				
				
					return false;
				}
			} else if (csNodeName == CString("Group"))
			{
				CString csGroupName;
				bool bRet = CCommonXML::GetAttributeValue(CString("name"), pXMLNode, csGroupName);
				if (!bRet)
				{
					pXMLNodeList->Release();
					pXMLNode->Release();

					return false;
				}

				CCollectionGroup* pNewGroup = pGroup->AddGroup(csGroupName);

				bRet = AddContentToGroup(pNewGroup, FileName, pXMLNode);		
				if (!bRet)
				{
					pXMLNodeList->Release();
					pXMLNode->Release();
					
					return false;
				}
			}
		
			pXMLNode->Release();
		}

		pXMLNodeList->Release();		

		return true;
	}

	static bool FillDataArray(
		CCollectionDataArray* pDataArray,
		CString& FileName,
        IXMLDOMNode* pXMLDataArray)
	{
		IXMLDOMNodeList* pXMLNodeList = NULL;
		HRESULT hr = pXMLDataArray->get_childNodes(&pXMLNodeList);
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
			IXMLDOMNode* pXMLNode = NULL;
			hr = pXMLNodeList->get_item(i, &pXMLNode);
			if (FAILED(hr))
			{
				pXMLNodeList->Release();

				return false;
			}			
		
			CString csFileName;
			bool bRet = CCommonXML::GetAttributeValue(CString("filename"), pXMLNode, csFileName);
			if (!bRet)
			{
				pXMLNodeList->Release();
				pXMLNode->Release();
				
				return false;
			}

			CString csFullFileName = CPath::RestoreFullName(FileName, csFileName);
			pDataArray->AddDataItem(csFullFileName);			
		
			pXMLNode->Release();		
		}

		pXMLNodeList->Release();
			
		return true;
	}

};