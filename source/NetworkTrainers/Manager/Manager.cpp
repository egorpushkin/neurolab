#include "StdAfx.h"
#include ".\manager.h"

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
	mTrainersContainer.SetAppFolder(csAppFolder);
	mTrainersContainer.CreateContainer();

	return TRUE;
}

BOOL CManager::ReleaseManagerInstance()
{
	mTrainersContainer.ReleaseContainer();

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
	case IDD_ITrainersContainer:
		mTrainersContainer.QueryInterface(iIDD, ppvObject);
		break;
	}
}