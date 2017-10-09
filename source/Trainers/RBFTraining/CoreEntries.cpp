#include "stdafx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "RBFTrainer.h"

ITrainer* CreateTrainerInstance()
{
	CRBFTrainer* pRBFTrainer = new CRBFTrainer;

	ITrainer* pTrainer = NULL;
	pRBFTrainer->QueryInterface(IDD_ITrainer, (void**)&pTrainer);
	
	return pTrainer;
}

void ReleaseTrainerInstance(ITrainer* pTrainer)
{
	if (pTrainer)
		delete pTrainer;
}