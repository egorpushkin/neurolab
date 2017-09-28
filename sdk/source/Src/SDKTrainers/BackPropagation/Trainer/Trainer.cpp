#include "TrainerMain.h"

#include "Trainer.h"

#include "../Source/Trainer/NetworkTrainer.h"

extern ulong objCount;

using namespace TrainersManagerKit;

namespace Trainer
{

	// {14065ea0-7b2c-4981-91eb-35af38e016d5} 
	DEFINE_GUID(CLSID_ThisTrainer, 
	0x14065ea0, 0x7b2c, 0x4981, 0x91, 0xeb, 0x35, 0xaf, 0x38, 0xe0, 0x16, 0xd5);

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
		ITrainerPtr trainerSelf(this, IID_ITrainer);

		AddTextMessage(trainerSelf, "N", "Training started.", "BP Trainer");

		result resultCode = S_OK;

		try
		{
			NetworkTrainer trainer;
			resultCode = trainer.DoTrain(trainerSelf);
		} 
		catch (...)
		{
			AddTextMessage(trainerSelf, "E", "Exception caught during training execution.", "BP Trainer");
			return E_FAIL;
		}

		if (SUCCEEDED(resultCode))
			AddTextMessage(trainerSelf, "N", "Training succeeded.", "BP Trainer");
		else
			AddTextMessage(trainerSelf, "E", "Training failed.", "BP Trainer");
		
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

		info->name_					= "BackPropagation";
		info->title_				= "Back Propagation Perceptron Training";
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
