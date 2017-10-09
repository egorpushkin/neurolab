#include "StdAfx.h"
#include "ExternalsManager.h"

#include "System\Directory.h"

CExtrenalsManager::CExtrenalsManager()
	: pBuilderControl(NULL)
	, csAppFolder(_T(""))
	, csMediaDirectory(_T(""))
{
}

void CExtrenalsManager::InitializeManager()
{
	ASSERT(csAppFolder != _T(""));

	// Enumerating 'Network Elements' folder entries
	CDirectoryEnumerator mDirEnum(csAppFolder + CString("\\NetworkElements\\*.dll"));
	mDirEnum.EnumerateDirectoryEntries();

	for(POSITION pos = mDirEnum.mFilesList.GetHeadPosition();pos;)
	{
		CString csFileName = mDirEnum.mFilesList.GetNext(pos);		
		CString csManagerFileName = csAppFolder+CString("\\NetworkElements\\")+csFileName;

		AddExternalManager(csManagerFileName, csFileName);
	}
}

void CExtrenalsManager::AddExternalManager(CString& csFilePath, CString& csFileName)
{
	CExternalManagerInstance* pExternalManagerInstance = 
		new CExternalManagerInstance();

	if (pExternalManagerInstance->LoadExternalManager(csFilePath))
		mContainers.AddTail(pExternalManagerInstance);
	else 
		delete pExternalManagerInstance;
}

void CExtrenalsManager::ProcessLoadMediaData()
{
	ASSERT(pBuilderControl != NULL);
	ASSERT(csAppFolder != _T(""));
	ASSERT(csMediaDirectory != _T(""));

	for (POSITION pos = mContainers.GetHeadPosition();pos;)
	{
		CExternalManagerInstance* pManagerInstance = mContainers.GetNext(pos);
		
		pManagerInstance->GetContainer()->SetAppFolder(csAppFolder);        
		pManagerInstance->GetContainer()->SetMediaDirectory(csMediaDirectory);        
		pManagerInstance->GetContainer()->SetBuilderControl(pBuilderControl);        

		pManagerInstance->GetContainer()->ProcessLoadMediaData();
	}
}

void CExtrenalsManager::ReleaseManager()
{
	RELEASE_LIST(mContainers, CExternalManagerInstance*, true)
}

// CExternalsManager tools
void CExtrenalsManager::SetBuilderControl(IBuilderControl* pControl)
{
	pBuilderControl = pControl;
}

void CExtrenalsManager::SetAppFolder(CString& AppFolder)
{
	csAppFolder = AppFolder;
}

void CExtrenalsManager::SetMediaDirectory(CString& MediaDir)
{
	csMediaDirectory = MediaDir;
}

// Elements operations
IElement* CExtrenalsManager::TryCreateElement(CString& ElementSysName)
{
	IElement* pElement = NULL;

	for (POSITION pos = mContainers.GetHeadPosition();pos;)
	{
		CExternalManagerInstance* pManagerInstance = mContainers.GetNext(pos);

		pElement = pManagerInstance->GetContainer()->TryCreateElement(ElementSysName);
        if (pElement)	
			break;
	}

	return pElement;
}

bool CExtrenalsManager::TryReleaseElement(IElement* pElement)
{
	bool bRet = false;

	for (POSITION pos = mContainers.GetHeadPosition();pos;)
	{
		CExternalManagerInstance* pManagerInstance = mContainers.GetNext(pos);

		bRet = pManagerInstance->GetContainer()->TryReleaseElement(pElement);
        if (bRet)	
			break;
	}

	return bRet;
}
