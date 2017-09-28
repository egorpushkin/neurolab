#include "TrainerMain.h"

#include "Trainer.h"

#include "../Source/NetworkTrainer.h"

extern ulong objCount;

using namespace TrainersManagerKit;

namespace Trainer
{

	// {dddb35e4-ae9d-4196-8324-9ed619517b1b} 
	DEFINE_GUID(CLSID_ThisTrainer, 
	0xdddb35e4, 0xae9d, 0x4196, 0x83, 0x24, 0x9e, 0xd6, 0x19, 0x51, 0x7b, 0x1b);

	Trainer::Trainer()
	{
		++objCount;
	}

	Trainer::~Trainer()
	{
		--objCount;
	}

	// IGeneralProcessor implementations section	
	result Trainer::Start()
	{
		ITrainer* piThis = NULL;
		QueryInterface(IID_ITrainer, (void**)&piThis);

		AddTextMessage(piThis, "N", "Training started.", "RBF Trainer");

		result resultCode = S_OK;

		try
		{
			NetworkTrainer trainer;
			resultCode = trainer.DoTrain(piThis);
		} 
		catch (...)
		{
			AddTextMessage(piThis, "E", "Exception caught during training execution.", "RBF Trainer");
			return E_FAIL;
		}

		if (SUCCEEDED(resultCode))
			AddTextMessage(piThis, "N", "Training succeeded.", "RBF Trainer");
		else
			AddTextMessage(piThis, "E", "Training failed.", "RBF Trainer");

		piThis->Release();
		
		return resultCode;
	}

	// ITrainer implementations section		
	result Trainer::GetTrainerInfo(PTRAINER_INFO info) const
	{
		if (!info)
			return E_FAIL;

		if (info->size_ != TRINFO_SIZE_V1 || 
			info->version_.size_ != VERINFO_SIZE_V1)
			return TR_E_INFOVERNOTSUPPORTED;

		info->name_					= "RBFStandardDeviation";
		info->title_				= "RBF Standard Deviation";
		info->clsid_				= CLSID_ThisTrainer;
		
		info->version_.verHi_		= 1;
		info->version_.verLow_		= 1;
		info->version_.verBuild_	= 101;
		info->version_.version_		= "1.1.101";

		return S_OK;
	}

	// ICommon implementations section	
	result Trainer::QueryInterface(REFIID iid, void** ppObject)
	{
		LOCAL_QI(iid, ppObject);

		*ppObject = NULL;
		return E_NOINTERFACE;
	}

} // namespace Trainer
