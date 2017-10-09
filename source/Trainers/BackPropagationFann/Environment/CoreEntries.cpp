#include "stdafx.h"

#include "interface_idds.h"

#include "../Trainer/BackProp.h"

#define DLL_FUNC_DECLARE_BP_FANN extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE_BP_FANN ITrainer* CreateTrainerInstance()
{
	CBackProp* pBackProp = new CBackProp;

	ITrainer* pTrainer = NULL;
	pBackProp->QueryInterface(IDD_ITrainer, (void**)&pTrainer);
	
	return pTrainer;
}

DLL_FUNC_DECLARE_BP_FANN void ReleaseTrainerInstance(ITrainer* pTrainer)
{
	if (pTrainer)
		delete pTrainer;
}