#include "StdAfx.h"
#include ".\manager.h"

#include "interface_idds.h"

CManager::CManager(void)
{
	pAppController = NULL;
}

CManager::~CManager(void)
{
}

// IManagerControl implementations section
BOOL CManager::InitializeManagerInstance()
{
	mFunctionsFactory.CreateFunctionsList();

	IFunctionsFactory* pFunctionsFactory = NULL;
	mFunctionsFactory.QueryInterface(IDD_IFunctionsFactory, (void**)&pFunctionsFactory);

	mGroupsContainer.SetAppFolder(csAppFolder);
	mGroupsContainer.SetFunctionsFactory(pFunctionsFactory);
	mGroupsContainer.BuildElementsStructure();

	return TRUE;
}

BOOL CManager::ReleaseManagerInstance()
{
	mGroupsContainer.ReleaseElementsStructure();

	mFunctionsFactory.ReleaseFunctionsList();

	return TRUE;
}

void CManager::SetAppFolder(CString& csFolder)
{
	csAppFolder = csFolder;
}

void CManager::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// IObject implementations section
CString	CManager::GetClassString()
{
	return CString("CManager");
}

void CManager::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IManagerControl:
		*ppvObject = (IManagerControl*)this;
		break;
	case IDD_IGroupsContainer:
		mGroupsContainer.QueryInterface(iIDD, ppvObject);
		break;
	case IDD_IFunctionsFactory:
		mFunctionsFactory.QueryInterface(iIDD, ppvObject);
		break;
	}
}