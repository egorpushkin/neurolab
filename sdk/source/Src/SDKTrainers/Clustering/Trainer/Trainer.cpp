#include "TrainerMain.h"

#include "Trainer.h"

#include "../Source/Chain/Chain.h"

extern ulong objCount;

using namespace TrainersManagerKit;

namespace Trainer
{

	// {28316e04-d47d-49d4-8e02-b198fe04d099} 
	DEFINE_GUID(CLSID_ThisTrainer, 
	0x28316e04, 0xd47d, 0x49d4, 0x8e, 0x02, 0xb1, 0x98, 0xfe, 0x04, 0xd0, 0x99);

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
		ITrainerPtr trainer(this, IID_ITrainer);

		AddTextMessage(trainer, "N", "Training started.", "Clustering");

		result resultCode = S_OK;

		try
		{
			ChainOfResp::IChainProcessorPtr chainProcessor = CreateChain(trainer);		
			resultCode = chainProcessor->ProcessChain();
		} 
		catch (...)
		{
			AddTextMessage(trainer, "E", "Exception caught during training execution.", "Clustering");
			return E_FAIL;
		}

		if (SUCCEEDED(resultCode))
			AddTextMessage(trainer, "N", "Training succeeded.", "Clustering");
		else
			AddTextMessage(trainer, "E", "Training failed.", "Clustering");
		
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

		info->name_					= "Clustering";
		info->title_				= "Clustering";
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
