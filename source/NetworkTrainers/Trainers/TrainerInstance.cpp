#include "StdAfx.h"
#include ".\trainerinstance.h"

CTrainerInstance::CTrainerInstance(CString& FileName)
{
	csTrainerFileName = FileName;

	hLibrary = NULL;

	pfnCreateTrainerInstance = NULL;
	pfnReleaseTrainerInstance = NULL;

	pTrainer = NULL;
}

CTrainerInstance::~CTrainerInstance(void)
{
	ReleaseTrainerInstance();
}

bool CTrainerInstance::CreateTrainerInstance()
{
	bool bRet = true;

	hLibrary = LoadLibrary(csTrainerFileName);
	if (!hLibrary)
		return false;

	(FARPROC &)pfnCreateTrainerInstance = GetProcAddress(hLibrary, "CreateTrainerInstance");
	if (!pfnCreateTrainerInstance)
	{
		ReleaseTrainerInstance();
		return false;
	}
	
	(FARPROC &)pfnReleaseTrainerInstance = GetProcAddress(hLibrary, "ReleaseTrainerInstance");
	if (!pfnReleaseTrainerInstance)
	{
		ReleaseTrainerInstance();
		return false;
	}

	pTrainer = (*pfnCreateTrainerInstance)();

	TRAINER_INFO tmInfo;					
	pTrainer->GetTrainerInfo(&tmInfo);

	return bRet;
}

void CTrainerInstance::ReleaseTrainerInstance()
{
	if (pTrainer)
	{
		(*pfnReleaseTrainerInstance)(pTrainer);
		pTrainer = NULL;
	}

	if (hLibrary)
	{
		FreeLibrary(hLibrary);
		hLibrary = NULL;
	}
}
