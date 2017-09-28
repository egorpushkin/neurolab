#include "StdAfx.h"
#include ".\solutionserialize.h"

#include "..\..\..\..\NeuroLab\LicenseKeeper\MD5Checksum\MD5Checksum.h"

bool CSolutionSerialize::LoadSolution(CExportSolution* pSolution)
{
	GetModuleFileName(
		GetModuleHandle(NULL), 
		pSolution->csAppFolder.GetBuffer(MAX_PATH), 
		MAX_PATH);
	pSolution->csAppFolder.ReleaseBuffer();

	int tmPos = pSolution->csAppFolder.ReverseFind('\\');
	pSolution->csAppFolder = pSolution->csAppFolder.Left(tmPos);

	CString csExportsSolution = pSolution->csAppFolder + 
		CString(_T("\\Exports\\ExportsSolution.xml"));

	// Checking solution config md5
	CFile tmConfFile;
	if (!tmConfFile.Open(csExportsSolution, CFile::modeRead, NULL))
		return false;	
	CString tmConfMD5 = CMD5Checksum::GetMD5(tmConfFile);
	tmConfFile.Close();

	if (tmConfMD5 != _T("1a29605c5fd8432d913fe0cac4c68823"))
		return false;

	// Loading solution
	CCommonXML tmXMLPraser(csExportsSolution);
	tmXMLPraser.CreateInstance();
	if (!tmXMLPraser.LoadFile())
		return false;

	IXMLDOMDocument* pXMLDom = tmXMLPraser.GetXMLDOMInstance();

	if (!VerifyRootSymbol(pXMLDom))
		return false;

    return EnumerateGroups(pSolution, pXMLDom);
}

bool CSolutionSerialize::VerifyRootSymbol(IXMLDOMDocument* pXMLDom)
{
	IXMLDOMElement* pXMLElement = NULL;
	HRESULT hr = pXMLDom->get_documentElement(&pXMLElement);
	if (FAILED(hr)) 
		return false;	

	USES_CONVERSION;

	CComBSTR bstrRootName;
	pXMLElement->get_baseName(&bstrRootName);
	
	if (CString(W2T(bstrRootName)) != CString("Exports"))
	{
		pXMLElement->Release();

		return false;
	}

	pXMLElement->Release();

    return true;
}

bool CSolutionSerialize::EnumerateGroups(
	CExportSolution* pSolution, 
	IXMLDOMDocument* pXMLDom)
{
	IXMLDOMNodeList* pXMLNodeList = NULL;
	HRESULT hr = pXMLDom->getElementsByTagName(CComBSTR("Group"), &pXMLNodeList);
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
		IXMLDOMNode* pXMLGroupNode = NULL;
		hr = pXMLNodeList->get_item(i, &pXMLGroupNode);
		if (FAILED(hr))
		{
			pXMLNodeList->Release();

			return false;				
		}

		CExportGroup* pExportGroup = new CExportGroup;

		if (!CCommonXML::GetAttributeValue(
			CString(_T("name")), 
			pXMLGroupNode, 
			pExportGroup->csGroupName))
		{	
			delete pExportGroup;
			pXMLGroupNode->Release();
			pXMLNodeList->Release();

			return false;
		}

		if (!CCommonXML::GetAttributeValue(
			CString(_T("subfolder")), 
			pXMLGroupNode, 
			pExportGroup->csGroupFolder))
		{	
			delete pExportGroup;
			pXMLGroupNode->Release();
			pXMLNodeList->Release();

			return false;
		}

		pSolution->AddGroup(pExportGroup);

		if (!EnumerateItems(pExportGroup, pXMLGroupNode))
		{
			pXMLGroupNode->Release();
			pXMLNodeList->Release();

            return false;		
		}	
	
		pXMLGroupNode->Release();
	}

	pXMLNodeList->Release();

	return true;
}

bool CSolutionSerialize::EnumerateItems(CExportGroup* pExportGroup, IXMLDOMNode* pXMLGroupNode)
{
	IXMLDOMNodeList* pXMLNodeList = NULL;
	HRESULT hr = pXMLGroupNode->get_childNodes(&pXMLNodeList);
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
		pXMLNode->get_nodeName(&bstrNodeName);

		USES_CONVERSION;
		
		CString csNodeName(W2T(bstrNodeName));
		if (bstrNodeName != _T("Item"))
		{
			pXMLNode->Release();
			pXMLNodeList->Release();	

			return false;
		}

		CExportItem* pExportItem = new CExportItem;

		if (!CCommonXML::GetAttributeValue(
			CString(_T("name")), 
			pXMLNode, 
			pExportItem->csItemName))
		{	
			delete pExportItem;
			pXMLNode->Release();
			pXMLNodeList->Release();

			return false;
		}

		if (!CCommonXML::GetAttributeValue(
			CString(_T("type")), 
			pXMLNode, 
			pExportItem->csItemType))
		{	
			delete pExportItem;
			pXMLNode->Release();
			pXMLNodeList->Release();

			return false;
		}

		if (!CCommonXML::GetAttributeValue(
			CString(_T("version")), 
			pXMLNode, 
			pExportItem->csItemVersion))
		{	
			delete pExportItem;
			pXMLNode->Release();
			pXMLNodeList->Release();

			return false;
		}

		if (!CCommonXML::GetAttributeValue(
			CString(_T("path_prefix")), 
			pXMLNode, 
			pExportItem->csItemPathPrefix))
		{	
			delete pExportItem;
			pXMLNode->Release();
			pXMLNodeList->Release();

			return false;
		}

		CComBSTR bstrDescription;
		pXMLNode->get_text(&bstrDescription);

		pExportItem->csItemDescription = W2T(bstrDescription);

		pExportGroup->AddItem(pExportItem);

		pXMLNode->Release();
	}

	pXMLNodeList->Release();	

	return true;
}

bool CSolutionSerialize::VerifySolution(CExportSolution* pExportSolution)
{
	pExportSolution->CreateEnumerator();
	while (CExportGroup* pExportGroup = pExportSolution->GetNextGroup())
	{
		pExportGroup->CreateEnumerator();
		while (CExportItem* pExportItem = pExportGroup->GetNextItem())
		{	
			if (pExportItem->csItemType == _T("project"))
				continue;

			CString csFileName = 
				pExportSolution->csAppFolder +
				CString("\\") + 
				pExportItem->csItemPathPrefix + 
				pExportItem->csItemName;

			WIN32_FIND_DATA FindFileData;
			HANDLE hFind;
			hFind = FindFirstFile(csFileName, &FindFileData);
			if (hFind == INVALID_HANDLE_VALUE) 
				return false;
			
		    FindClose(hFind);
		}
	}

	return true;
}