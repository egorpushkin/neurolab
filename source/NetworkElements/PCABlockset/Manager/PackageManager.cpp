#include "StdAfx.h"
#include "PackageManager.h"

#include "interface_idds.h"
#include "..\Elements\PackageElements.h"

CPackageManager::CPackageManager()
{
	CreateElementsStructure();
}

CPackageManager::~CPackageManager()
{
	RELEASE_LIST(mElements, sElement*, true);
	RELEASE_LIST(mSessionAllocations, IElement*, true);
}

// IExternalElementsContainer implementations section
// CScriptsNetManager init
void CPackageManager::ProcessLoadMediaData()
{
	ASSERT(pBuilderControl != NULL);
	ASSERT(csAppFolder != _T(""));
	ASSERT(csMediaDirectory != _T(""));

	IOutputDevice* pOutputDevice = NULL;
	pBuilderControl->QueryInterface(IDD_IOutputDevice, (void**)&pOutputDevice);

	CString tmMediaPrefix = CString(_T("\\NetworkElements\\Media"));

	// Load required media data using the following syntax:
	//
	//	pOutputDevice->LoadImage(tmMediaPrefix + CString(_T("\\")) + CString(_T("Your_Bitmap_File_Name.bmp")), CString(_T("Your_Bitmap_Id")));
	//

	pOutputDevice->LoadImage(tmMediaPrefix + CString(_T("\\")) + CString(_T("PCA_Transform_Active.bmp")), CString(_T("PCA_Transform_Active")));
	pOutputDevice->LoadImage(tmMediaPrefix + CString(_T("\\")) + CString(_T("PCA_Transform_Passive.bmp")), CString(_T("PCA_Transform_Passive")));
}

// Elements oparations
IElement* CPackageManager::TryCreateElement(CString& ElementSysName)
{
	IElement* pElement = NULL;

	// Add allocation code using the following syntax:
	//
	//	if (ElementSysName == _T("YourElement"))
	//	{
	//		CYourElement* pYourElement = new CYourElement;
	//		pYourElement->QueryInterface(IDD_IElement, (void**)&pElement);
	//	}	
	//

	if (ElementSysName == _T("PCATransform"))
	{
		CPCATranform* pPCATransform = new CPCATranform;
		pPCATransform->QueryInterface(IDD_IElement, (void**)&pElement);
	}

	if (pElement)
		mSessionAllocations.AddTail(pElement);

	return pElement;
}

bool CPackageManager::TryReleaseElement(IElement* pElement)
{
	POSITION posElement = mSessionAllocations.Find(pElement);
	if (!posElement)
		return false;

	mSessionAllocations.RemoveAt(posElement);
	delete pElement;
	
	return true;
}

// Elements info
CString CPackageManager::GetGroupName()
{
	return _T("PCA Blockset");
}

// CScriptsNetManager tools
void CPackageManager::SetBuilderControl(IBuilderControl* pControl)
{
	pBuilderControl = pControl;
}

void CPackageManager::SetAppFolder(CString& AppFolder)
{
	csAppFolder = AppFolder;
}

void CPackageManager::SetMediaDirectory(CString& MediaDir)
{
	csMediaDirectory = MediaDir;
}

// IObject implementations section
CString CPackageManager::GetClassString()		
{
	return _T("CPackageManager");
}

void CPackageManager::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_IExternalManager:
		*ppvObject = (IExternalElementsContainer*)this;
		break;
	}
}

// CScriptsNetManager internal private tools
void CPackageManager::CreateElementsStructure()
{
	// Add elements structure using the following syntax:
	//
	//	sElement* pElement = new sElement(CString(_T("YourElement")), CString(_T("Your Element")));
	//	mElements.AddTail(pElement);
	//

	sElement* pElement = new sElement(CString(_T("PCATransform")), CString(_T("PCA Transform")));
	mElements.AddTail(pElement);
}