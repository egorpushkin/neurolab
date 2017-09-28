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

	pOutputDevice->LoadImage(tmMediaPrefix + CString("\\") + CString("Canny_Detector_Passive.bmp"), CString("Canny_Detector_Passive"));
	pOutputDevice->LoadImage(tmMediaPrefix + CString("\\") + CString("Canny_Detector_Active.bmp"), CString("Canny_Detector_Active"));
}

// Elements oparations
IElement* CPackageManager::TryCreateElement(CString& ElementSysName)
{
	IElement* pElement = NULL;

	if (ElementSysName == _T("CannyDetector"))
	{
		CCannyDetector* pCannyDetector = new CCannyDetector;
		pCannyDetector->QueryInterface(IDD_IElement, (void**)&pElement);
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
	return _T("Edge Detectors");
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
	sElement* pElement = new sElement(CString(_T("CannyDetector")), CString(_T("Canny Detector")));
	mElements.AddTail(pElement);
}