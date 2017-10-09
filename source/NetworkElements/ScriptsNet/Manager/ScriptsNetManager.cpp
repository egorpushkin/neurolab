#include "StdAfx.h"
#include "ScriptsNetManager.h"

#include "interface_idds.h"
#include "..\Elements\PackageElements.h"

CScriptsNetManager::CScriptsNetManager()
{
	CreateElementsStructure();
}

CScriptsNetManager::~CScriptsNetManager()
{
	RELEASE_LIST(mElements, sElement*, true);
	RELEASE_LIST(mSessionAllocations, IElement*, true);
}

// IExternalElementsContainer implementations section
// CScriptsNetManager init
void CScriptsNetManager::ProcessLoadMediaData()
{
	ASSERT(pBuilderControl != NULL);
	ASSERT(csAppFolder != _T(""));
	ASSERT(csMediaDirectory != _T(""));

	IOutputDevice* pOutputDevice = NULL;
	pBuilderControl->QueryInterface(IDD_IOutputDevice, (void**)&pOutputDevice);

	CString tmMediaPrefix = CString(_T("\\NetworkElements\\Media"));

	pOutputDevice->LoadImage(tmMediaPrefix + CString("\\") + CString("Scripting_Element_Passive.bmp"), CString("Scripting_Element_Passive"));
	pOutputDevice->LoadImage(tmMediaPrefix + CString("\\") + CString("Scripting_Element_Active.bmp"), CString("Scripting_Element_Active"));
}

// Elements oparations
IElement* CScriptsNetManager::TryCreateElement(CString& ElementSysName)
{
	IElement* pElement = NULL;

	if (ElementSysName == _T("ScriptingElement"))
	{
		CScriptingElement* pScriptingElement = new CScriptingElement;
		pScriptingElement->QueryInterface(IDD_IElement, (void**)&pElement);
	}	

	if (pElement)
		mSessionAllocations.AddTail(pElement);

	return pElement;
}

bool CScriptsNetManager::TryReleaseElement(IElement* pElement)
{
	POSITION posElement = mSessionAllocations.Find(pElement);
	if (!posElement)
		return false;

	mSessionAllocations.RemoveAt(posElement);
	delete pElement;
	
	return true;
}

// Elements info
CString CScriptsNetManager::GetGroupName()
{
	return _T("Scripting Extension");
}

// CScriptsNetManager tools
void CScriptsNetManager::SetBuilderControl(IBuilderControl* pControl)
{
	pBuilderControl = pControl;
}

void CScriptsNetManager::SetAppFolder(CString& AppFolder)
{
	csAppFolder = AppFolder;
}

void CScriptsNetManager::SetMediaDirectory(CString& MediaDir)
{
	csMediaDirectory = MediaDir;
}

// IObject implementations section
CString CScriptsNetManager::GetClassString()		
{
	return _T("CScriptsNetManager");
}

void CScriptsNetManager::QueryInterface(int iIDD, void** ppvObject)
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
void CScriptsNetManager::CreateElementsStructure()
{
	sElement* pElement = new sElement(CString(_T("ScriptingElement")), CString(_T("Scripting Element")));
	mElements.AddTail(pElement);
}