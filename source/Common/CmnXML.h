#pragma once

#include "CmnObjects.h"

//#pragma comment(lib,"msxml.lib")
#include <msxml.h>

interface IXMLStorageController : public IObject
{
	virtual bool			Serialize(IXMLDOMDocument* pXMLDom, bool bIsLoad) = 0;
};

class CCommonXML
{
public:
	CCommonXML()
		: pXMLDom(NULL)
		, csFileName(_T(""))
	{}

	CCommonXML(CString& FileName)
		: pXMLDom(NULL)
		, csFileName(FileName)
	{}

	~CCommonXML()
	{
		ReleaseInstance();
	}

	void SetFileName(CString& FileName)
	{
		csFileName = FileName;
	}

	void CreateInstance()
	{
		if (pXMLDom)
			ReleaseInstance();

		HRESULT hr = CoInitialize(NULL);
		hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, 
			IID_IXMLDOMDocument, (void**)&pXMLDom);
		if (FAILED(hr)) 
			return;

		pXMLDom->put_async(VARIANT_FALSE);
	}

	void ReleaseInstance()
	{
		if (pXMLDom)
		{
			pXMLDom->Release();
			pXMLDom = NULL;
		}	

		CoUninitialize();
	}

	IXMLDOMDocument* GetXMLDOMInstance()
	{
		return pXMLDom;
	}

	bool LoadFile()
	{
		if (!pXMLDom || csFileName == _T(""))
			return false;

		VARIANT_BOOL bvResult; 
		pXMLDom->load(COleVariant(csFileName), &bvResult);
		if (bvResult == VARIANT_FALSE)
			return false;
	
		return true;
	}

	bool SaveFile()
	{
		if (!pXMLDom || csFileName == _T(""))
			return false;

		HRESULT hr = pXMLDom->save(COleVariant(csFileName));
		if (FAILED(hr))
			return false;

		return true;
	}

	// static operators
	static IXMLDOMNode* CreateParentNode(
		CString& csNodeName,
		IXMLDOMNode* pCurrentNode, 
		IXMLDOMDocument* pXMLDocument)
	{
		CComVariant varNodeType = NODE_ELEMENT;
		CComBSTR bstrNode(csNodeName);
		CComBSTR bstrNamespaceURI = "";
		IXMLDOMNode* pXMLNode = NULL;
		HRESULT hr = pXMLDocument->createNode(varNodeType, bstrNode, bstrNamespaceURI,
			&pXMLNode);
		if (FAILED(hr))
			return NULL;

		IXMLDOMNode* pXMLNewNode = NULL;
		hr = pCurrentNode->appendChild(pXMLNode, &pXMLNewNode);
		if (FAILED(hr))
		{
			pXMLNode->Release();

			return NULL;		
		}

		pXMLNode->Release();

        return pXMLNewNode;
	}

	static IXMLDOMNode* CreateParentNode(
		CString& csNodeName,
		IXMLDOMElement* pXMLCurrentElement,
		IXMLDOMDocument* pXMLDocument)
	{
		IXMLDOMNode* pXMLCurrentNode = NULL;		
		HRESULT hr = pXMLCurrentElement->QueryInterface(IID_IXMLDOMNode, 
			(void**)&pXMLCurrentNode);
		if (FAILED(hr))
			return NULL;

		IXMLDOMNode* pXMLNewNode = CreateParentNode(csNodeName, pXMLCurrentNode, pXMLDocument);
		
		pXMLCurrentNode->Release();

        return pXMLNewNode;
	}

	static bool AddAttribute(
		CString& csAttributeName, 
		CString& csAttributeValue, 
		IXMLDOMNode* pCurrentNode, 
		IXMLDOMDocument* pXMLDocument)
	{
		CComBSTR bstrAttr(csAttributeName);
		IXMLDOMAttribute* pXMLAttr = NULL;
		HRESULT hr = pXMLDocument->createAttribute(bstrAttr, &pXMLAttr);
		if (FAILED(hr))
			return false;

		pXMLAttr->put_value(CComVariant(csAttributeValue));

		IXMLDOMNamedNodeMap* pXMLNamedNodeMap = NULL;
		hr = pCurrentNode->get_attributes(&pXMLNamedNodeMap);
		if (FAILED(hr))
		{	
			pXMLAttr->Release();

			return false;
		}

		IXMLDOMNode* pXMLAttrNode = NULL;
		hr = pXMLNamedNodeMap->setNamedItem(pXMLAttr, &pXMLAttrNode);
		if (FAILED(hr))
		{
			pXMLAttr->Release();
			pXMLNamedNodeMap->Release();

			return false;
		}

		pXMLAttr->Release();
		pXMLNamedNodeMap->Release();
		pXMLAttrNode->Release();

		return true;
	}

	static bool GetAttributeValue(
			CString& csAttributeName, 
			IXMLDOMNode* pXMLNode,
			CString& csAttributeValue)
	{
		IXMLDOMNamedNodeMap* pXMLNamedNodeMap = NULL;
		HRESULT hr = pXMLNode->get_attributes(&pXMLNamedNodeMap);
        if (FAILED(hr))
			return false;

		IXMLDOMNode* pXMLAttrNode = NULL;
		hr = pXMLNamedNodeMap->getNamedItem(CComBSTR(csAttributeName), &pXMLAttrNode);
		if (FAILED(hr) || !pXMLAttrNode)
		{
			pXMLNamedNodeMap->Release();
		
			return false;
		}

		IXMLDOMAttribute* pXMLAttribute = NULL;
		hr = pXMLAttrNode->QueryInterface(IID_IXMLDOMAttribute, (void**)&pXMLAttribute);
		if (FAILED(hr))
		{
			pXMLNamedNodeMap->Release();
			pXMLAttrNode->Release();
		
			return false;		
		}

		VARIANT varAttributeValue;
		pXMLAttribute->get_value(&varAttributeValue);
		
		pXMLAttribute->Release();
		pXMLAttrNode->Release();
		pXMLNamedNodeMap->Release();

		USES_CONVERSION;
		csAttributeValue = CString(W2T(varAttributeValue.bstrVal));
		
        return true;	
	}

	static bool GetAttributeValue(
			CString& csAttributeName, 
			IXMLDOMElement* pXMLElement,
			CString& csAttributeValue)
	{
		IXMLDOMNode* pXMLNode = NULL;		
		HRESULT hr = pXMLElement->QueryInterface(IID_IXMLDOMNode, 
			(void**)&pXMLNode);
		if (FAILED(hr))
			return false;

		bool bRet = GetAttributeValue(csAttributeName, pXMLNode, csAttributeValue);
		
		pXMLNode->Release();

        return bRet;
	}

private:
	CString				csFileName;
	
	IXMLDOMDocument*	pXMLDom;
};