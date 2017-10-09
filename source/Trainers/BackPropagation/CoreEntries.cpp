#include "stdafx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "BackProp.h"

ITrainer* CreateTrainerInstance()
{
	CBackProp* pBackProp = new CBackProp;

	ITrainer* pTrainer = NULL;
	pBackProp->QueryInterface(IDD_ITrainer, (void**)&pTrainer);
	
	return pTrainer;
}

void ReleaseTrainerInstance(ITrainer* pTrainer)
{
	if (pTrainer)
		delete pTrainer;
}