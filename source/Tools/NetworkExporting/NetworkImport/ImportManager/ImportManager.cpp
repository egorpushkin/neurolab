#include "StdAfx.h"
#include "ImportManager.h"

#include "interface_idds.h"

CImportManager::CImportManager()
{
	bIsInitialized = false;
}

CImportManager::~CImportManager()
{
	if (bIsInitialized)
		RelaseManager();
}

// IImportManager implementations section	
bool CImportManager::InitializeManager()
{
	bool bRet = mBuilderElementsComponent.LoadComponent();
	if (!bRet)
		return false;

	IGroupsContainer* pGroupsContainer = NULL;
	IFunctionsFactory* pFunctionsFactory = NULL;

	mBuilderElementsComponent.QueryInterface(IDD_IGroupsContainer, (void**)&pGroupsContainer);	
	mBuilderElementsComponent.QueryInterface(IDD_IFunctionsFactory, (void**)&pFunctionsFactory);

	if (!pGroupsContainer || !pFunctionsFactory)
		return false;

	mNeuroFactoryMng.SetBuilderElementsObjects(pGroupsContainer, pFunctionsFactory);

	bIsInitialized = true;

	return true;
}

void CImportManager::RelaseManager()
{
	mNeuroFactoryMng.ReleaseElementsList();
	mBuilderElementsComponent.UnloadComponent();

	bIsInitialized = false;
}

bool CImportManager::LoadNLProject(CString& FileName)
{
	if (!bIsInitialized)
		return false;

	bool bRet = false;

	CFile cfLoadFile;
	if (cfLoadFile.Open(FileName, CFile::modeRead, NULL))
	{
		CArchive ar(&cfLoadFile, CArchive::load);
		if (mNeuroFactoryMng.Serialize(ar))
			bRet = true;

		ar.Close();
		cfLoadFile.Close();
	}		

	return bRet;
}

// IObject implementations section	
CString CImportManager::GetClassString()
{
	return _T("CImportManager");
}

void CImportManager::QueryInterface(int iIDD, void** ppvObject)
{
	switch (iIDD)
	{
	case IDD_IImportManager:
		*ppvObject = (IImportManager*)this;
		break;
	case IDD_INetworkProcessor:
		mNeuroFactoryMng.QueryInterface(iIDD, ppvObject);
		break;
	case IDD_IElementsCollection:
		mNeuroFactoryMng.QueryInterface(iIDD, ppvObject);
		break;
	}
}
