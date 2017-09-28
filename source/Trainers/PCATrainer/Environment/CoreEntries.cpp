#include "stdafx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "../Trainer/PCATrainerImpl.h"

ITrainer* CreateTrainerInstance()
{
	CPCATrainerImpl* pPCATrainer = new CPCATrainerImpl;

	ITrainer* pTrainer = NULL;
	pPCATrainer->QueryInterface(IDD_ITrainer, (void**)&pTrainer);
	
	return pTrainer;
}

void ReleaseTrainerInstance(ITrainer* pTrainer)
{
	if (pTrainer)
		delete pTrainer;
}