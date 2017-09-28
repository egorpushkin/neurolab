#include "stdafx.h"
#include "CoreEntries.h"

#include "interface_idds.h"
#include "KohonenTrainer.h"

ITrainer* CreateTrainerInstance()
{
	CKohonenTrainer* pKohonenTrainer = new CKohonenTrainer;

	ITrainer* pTrainer = NULL;
	pKohonenTrainer->QueryInterface(IDD_ITrainer, (void**)&pTrainer);
	
	return pTrainer;
}

void ReleaseTrainerInstance(ITrainer* pTrainer)
{
	if (pTrainer)
		delete pTrainer;
}