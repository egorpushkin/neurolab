#include "StdAfx.h"
#include "SolutionSerialize.h"

#include "System\Directory.h"

bool CSolutionOperation_Serialize::Save(
	CScriptSolution* pSolution, 
	IXMLDOMDocument* pXMLDom)
{
	CString csRootXML = CString(_T("<?xml version=\"1.0\"?> \
    	<ScriptingSolution name=\"") + 
		pSolution->GetSolutionName() +
		CString("\"></ScriptingSolution>"));
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
	bool bRet = AddItems(pSolution, pXMLElement, pXMLDom);
	if (!bRet)
	{
		pXMLElement->Release();
		return false;
	}
	bRet = AddDataItems(pSolution, pXMLElement, pXMLDom);
	if (!bRet)
	{
		pXMLElement->Release();
		return false;
	}
	bRet = AddBitmaps(pSolution, pXMLElement, pXMLDom);
	if (!bRet)
	{
		pXMLElement->Release();
		return false;
	}
	bRet = AddProjects(pSolution, pXMLElement, pXMLDom);
	if (!bRet)
	{
		pXMLElement->Release();
		return false;
	}

	pXMLElement->Release(); 	

	return bRet;
}

bool CSolutionOperation_Serialize::AddItems(
	CScriptSolution* pSolution, 
	IXMLDOMElement* pXMLElement,
	IXMLDOMDocument* pXMLDom)
{
	pSolution->CreateEnumerator();
	while (CSolutionItem* pItem = pSolution->GetNextItem())
	{
		// Creating script item node
		IXMLDOMNode* pXMLItemNode = CCommonXML::CreateParentNode(
			CString("ScriptItem"), pXMLElement, pXMLDom);
		if (!pXMLItemNode)
			return false;

		CString tmFileName = CPath::GetRelativePath(pSolution->GetFileName(), 
			pItem->GetFileName());

		// Adding filename attribute
		if (!CCommonXML::AddAttribute(CString("filename"), 
			tmFileName, pXMLItemNode, pXMLDom))
		{
			pXMLItemNode->Release();

			return false;
		}

		CComBSTR tmText(pItem->GetDescription());
		pXMLItemNode->put_text(tmText);

		pXMLItemNode->Release();	
	}	

	return true;
}

bool CSolutionOperation_Serialize::AddDataItems(
	CScriptSolution* pSolution, 
	IXMLDOMElement* pXMLElement,
	IXMLDOMDocument* pXMLDom)
{
	pSolution->CreateDataEnumerator();
	while (CDataFileItem* pItem = pSolution->GetNextDataItem())
	{
		// Creating script item node
		IXMLDOMNode* pXMLItemNode = CCommonXML::CreateParentNode(
			CString("DataItem"), pXMLElement, pXMLDom);
		if (!pXMLItemNode)
			return false;

		CString tmFileName = CPath::GetRelativePath(pSolution->GetFileName(), 
			pItem->GetFileName());

		// Adding filename attribute
		if (!CCommonXML::AddAttribute(CString("filename"), 
			tmFileName, pXMLItemNode, pXMLDom))
		{
			pXMLItemNode->Release();

			return false;
		}

		pXMLItemNode->Release();	
	}		

	return true;	
}

bool CSolutionOperation_Serialize::AddBitmaps(
	CScriptSolution* pSolution, 
	IXMLDOMElement* pXMLElement,
	IXMLDOMDocument* pXMLDom)
{
	pSolution->CreateBitmapsEnumerator();
	while (CBitmapItem* pItem = pSolution->GetNextBitmap())
	{
		// Creating script item node
		IXMLDOMNode* pXMLItemNode = CCommonXML::CreateParentNode(
			CString("BitmapItem"), pXMLElement, pXMLDom);
		if (!pXMLItemNode)
			return false;

		CString tmFileName = CPath::GetRelativePath(pSolution->GetFileName(), 
			pItem->GetFileName());

		// Adding filename attribute
		if (!CCommonXML::AddAttribute(CString("filename"), 
			tmFileName, pXMLItemNode, pXMLDom))
		{
			pXMLItemNode->Release();

			return false;
		}

		pXMLItemNode->Release();	
	}		

	return true;	
}

bool CSolutionOperation_Serialize::AddProjects(
	CScriptSolution* pSolution, 
	IXMLDOMElement* pXMLElement,
	IXMLDOMDocument* pXMLDom)
{
	pSolution->CreateProjectsEnumerator();
	while (CProjectItem* pItem = pSolution->GetNextProject())
	{
		// Creating script item node
		IXMLDOMNode* pXMLItemNode = CCommonXML::CreateParentNode(
			CString("ProjectItem"), pXMLElement, pXMLDom);
		if (!pXMLItemNode)
			return false;

		CString tmFileName = CPath::GetRelativePath(pSolution->GetFileName(), 
			pItem->GetFileName());

		// Adding filename attribute
		if (!CCommonXML::AddAttribute(CString("filename"), 
			tmFileName, pXMLItemNode, pXMLDom))
		{
			pXMLItemNode->Release();

			return false;
		}

		pXMLItemNode->Release();	
	}		

	return true;	
}

bool CSolutionOperation_Serialize::Load(
	CScriptSolution* pSolution, 
	IXMLDOMDocument* pXMLDom)
{
	IXMLDOMElement* pXMLElement = NULL;
	HRESULT hr = pXMLDom->get_documentElement(&pXMLElement);
	if (FAILED(hr)) 
		return false;	

	USES_CONVERSION;

	CComBSTR bstrRootName;
	pXMLElement->get_baseName(&bstrRootName);
	
	if (CString(W2T(bstrRootName)) != CString("ScriptingSolution"))
	{
		pXMLElement->Release();

		return false;
	}

	CString csSolutionName;
	if (!CCommonXML::GetAttributeValue(CString("name"), 
		pXMLElement, csSolutionName))
	{
		pXMLElement->Release();

		return false;	
	}

	pSolution->SetSolutionName(csSolutionName);

	pXMLElement->Release();

	// Parsing Script Items
	IXMLDOMNodeList* pXMLNodeList = NULL;
	hr = pXMLDom->getElementsByTagName(CComBSTR("ScriptItem"), &pXMLNodeList);
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

		CString tmRelativeFile;
		if (!CCommonXML::GetAttributeValue(CString("filename"), 
			pXMLItemNode, tmRelativeFile))
			continue;

		CString tmAbsoluteFile = CPath::RestoreFullName(pSolution->GetFileName(),
			tmRelativeFile);

		CComBSTR bstrDescription;
		pXMLItemNode->get_text(&bstrDescription);

		pSolution->AddItem(tmAbsoluteFile, CString(W2T(bstrDescription)), false);
	
		pXMLItemNode->Release();
	}

	pXMLNodeList->Release();

	// Parsing Data Items
	pXMLNodeList = NULL;
	hr = pXMLDom->getElementsByTagName(CComBSTR("DataItem"), &pXMLNodeList);
	if (FAILED(hr))
		return false;

    lCount = 0; 
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

		CString tmRelativeFile;
		if (!CCommonXML::GetAttributeValue(CString("filename"), 
			pXMLItemNode, tmRelativeFile))
			continue;

		CString tmAbsoluteFile = CPath::RestoreFullName(pSolution->GetFileName(),
			tmRelativeFile);

		pSolution->AddDataFile(tmAbsoluteFile);
	
		pXMLItemNode->Release();
	}

	pXMLNodeList->Release();

	// Parsing Bitmap Items
	pXMLNodeList = NULL;
	hr = pXMLDom->getElementsByTagName(CComBSTR("BitmapItem"), &pXMLNodeList);
	if (FAILED(hr))
		return false;

    lCount = 0; 
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

		CString tmRelativeFile;
		if (!CCommonXML::GetAttributeValue(CString("filename"), 
			pXMLItemNode, tmRelativeFile))
			continue;

		CString tmAbsoluteFile = CPath::RestoreFullName(pSolution->GetFileName(),
			tmRelativeFile);

		pSolution->AddBitmapFile(tmAbsoluteFile);
	
		pXMLItemNode->Release();
	}

	pXMLNodeList->Release();

	// Parsing Project Items
	pXMLNodeList = NULL;
	hr = pXMLDom->getElementsByTagName(CComBSTR("ProjectItem"), &pXMLNodeList);
	if (FAILED(hr))
		return false;

    lCount = 0; 
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

		CString tmRelativeFile;
		if (!CCommonXML::GetAttributeValue(CString("filename"), 
			pXMLItemNode, tmRelativeFile))
			continue;

		CString tmAbsoluteFile = CPath::RestoreFullName(pSolution->GetFileName(),
			tmRelativeFile);

		pSolution->AddProjectFile(tmAbsoluteFile);
	
		pXMLItemNode->Release();
	}

	pXMLNodeList->Release();

	return true;
}
