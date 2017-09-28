#include "StdAfx.h"
#include ".\trainersmanager.h"

#include "interface_idds.h"

#include "System\Directory.h"

CTrainersManager::CTrainersManager(void)
{
}

CTrainersManager::~CTrainersManager(void)
{
	ReleaseContainer();
}

void CTrainersManager::SetAppFolder(CString& csFolder)
{
	csAppFolder = csFolder;
}

void CTrainersManager::CreateContainer()
{
	LoadInstalledTrainers();
}

void CTrainersManager::LoadInstalledTrainers()
{
	CDirectoryEnumerator mDirEnum(csAppFolder + CString("\\Trainers\\*.dll"));
	mDirEnum.EnumerateDirectoryEntries();

	for(POSITION pos = mDirEnum.mFilesList.GetHeadPosition();pos;)
	{
		CString csFileName = mDirEnum.mFilesList.GetNext(pos);		
		CString csTrainerFileName = csAppFolder+CString("\\Trainers\\")+csFileName;

		AddTrainer(csTrainerFileName, csFileName);
	}
}

void CTrainersManager::AddTrainer(CString& csPluginFilePath, CString& csPluginFileName)
{
	CTrainerInstance* pTrainerInstance = new CTrainerInstance(csPluginFilePath);

	if (pTrainerInstance->CreateTrainerInstance())
	{
		mTrainerInstances.AddTail(pTrainerInstance);
		mTrainers.AddTail(pTrainerInstance->pTrainer);
	}
	else 
		delete pTrainerInstance;
}

void CTrainersManager::ReleaseContainer()
{
	for (;mTrainerInstances.GetCount()>0;)
	{		
		CTrainerInstance* pTrainerInstance = mTrainerInstances.GetHead();
		mTrainerInstances.RemoveHead();

        delete pTrainerInstance;
	}	
}

// IObject implementations section
CString	CTrainersManager::GetClassString()
{
	return CString("CTrainersManager");
}

void CTrainersManager::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_ITrainersContainer:
		*ppvObject = (ITrainersContainer*)this;
		break;
	}
}