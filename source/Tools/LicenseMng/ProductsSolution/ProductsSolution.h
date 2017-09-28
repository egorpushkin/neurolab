#pragma once

#include "Templates\Enumerator.h"
#include "CmnXML.h"

#include "..\..\NeuroLab\LicenseKeeper\ssdhelper.h"

class CProduct
{
public:
	CString			csTitle;
	CString			csName;
	CString			csPublicKey;
	CString			csPrivateKey;
};

class CProductsSolution
{
public:
	CProductsSolution(CString& AppFolder)
		: csAppFolder(AppFolder)
	{	
	}

	~CProductsSolution()
	{
		RELEASE_LIST(mProductsList, CProduct*, true)
	}


	bool			LoadSolution()
	{
		// Verifying products list file
		CString csProductsFile = csAppFolder + 
			CString(_T("\\ProductsFamily.xml"));

		// Checking md5
		CFile tmConfFile;
		if (!tmConfFile.Open(csProductsFile, CFile::modeRead, NULL))
			return false;	
		CString tmConfMD5 = CMD5Checksum::GetMD5(tmConfFile);
		tmConfFile.Close();

		if (tmConfMD5 != _T("db3baeb0e4f7b04819a4136df2df37f2"))
			return false;

		// Loading products list
		CCommonXML tmXMLPraser(csProductsFile);
		tmXMLPraser.CreateInstance();
		if (!tmXMLPraser.LoadFile())
			return false;

		IXMLDOMDocument* pXMLDom = tmXMLPraser.GetXMLDOMInstance();	

		return EnumerateProducts(pXMLDom);
	}

	ENUMERATOR(mProductsList, CProduct*, CreateEnumerator, GetNextProduct, posProducts)

private:
	CList<CProduct*, CProduct*> mProductsList;

	CString			csAppFolder;

	bool EnumerateProducts(
		IXMLDOMDocument* pXMLDom)
	{
		IXMLDOMNodeList* pXMLNodeList = NULL;
		HRESULT hr = pXMLDom->getElementsByTagName(CComBSTR("product"), &pXMLNodeList);
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
			IXMLDOMNode* pXMLProductNode = NULL;
			hr = pXMLNodeList->get_item(i, &pXMLProductNode);
			if (FAILED(hr))
			{
				pXMLNodeList->Release();

				return false;				
			}

			CProduct* pProduct = new CProduct;
			
			CCommonXML::GetAttributeValue(
				CString(_T("title")), 
				pXMLProductNode, 
				pProduct->csTitle);
			
			CCommonXML::GetAttributeValue(
				CString(_T("name")), 
				pXMLProductNode, 
				pProduct->csName);

			CCommonXML::GetAttributeValue(
				CString(_T("public_key")), 
				pXMLProductNode, 
				pProduct->csPublicKey);

			CCommonXML::GetAttributeValue(
				CString(_T("private_key")), 
				pXMLProductNode, 
				pProduct->csPrivateKey);			
			
			mProductsList.AddTail(pProduct);

			pXMLProductNode->Release();
		}
		
		pXMLNodeList->Release();

		return true;		
	}
};