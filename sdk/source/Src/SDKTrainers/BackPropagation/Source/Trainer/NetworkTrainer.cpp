#include "fann.h"

#include "TrainerMain.h"

#include "NetworkTrainer.h"

#include "../NetworkParser/GenericNetwork.h"
#include "../NetworkParser/AutomaticParser.h"

#include "FannTrainer.h"

namespace Trainer
{

	NetworkTrainer::NetworkTrainer()
		: networkProcessor_()
		, trainData_()
	{
	}

	NetworkTrainer::~NetworkTrainer()
	{
	}

	result NetworkTrainer::DoTrain(TrMngKit::ITrainerRef trainer)
	{
		if ( FAILED(CaptureNetwork(trainer->GetNetwork(TrMngKit::PID_PrimaryParam1))) )
			return E_FAIL;

		if ( FAILED(CaptureData(trainer->GetDataObject(TrMngKit::PID_PrimaryParam1))) )
			return E_FAIL;

		// Create generic network object to store perceptron pattern
		GenericNetworkPtr genericNet(
			new GenericNetwork(
				trainer, 
				NiKit::IElementsCollectionPtr(networkProcessor_, NiKit::IID_IElementsCollection), 
				trainData_
			)
		);
		
		// Create parser object
        AutomaticParserPtr autoParser(
			new AutomaticParser(
				genericNet
			) 	
		);

		// Construct network pattern
		result r = autoParser->DoConstructNetwork();
        if ( FAILED(r) )
		{
			AddTextMessage(trainer, "E", "Error creating network pattern.", "BP Trainer");
			return r;
		}

		// Verify network before starting training
		if ( FAILED(genericNet->CompliteVerification()) )
			return E_FAIL;

		// Train pattern
		try
		{
			FannTrainer fannTrainer(genericNet);
			r = fannTrainer.DoTrainNetwork();
		}
		catch ( ... )
		{
			AddTextMessage(trainer, "E", "Exception caught during FannTrainer::DoTrainNetwork() execution.", StringA("BP Trainer"));
			return E_FAIL;
		}

		return r;
	}

	result NetworkTrainer::CaptureNetwork(NiKit::INetworkProcessorRef networkProcessor)
	{
		networkProcessor_ = networkProcessor;
		return (networkProcessor_ ? S_OK : E_FAIL);
	}

	result NetworkTrainer::CaptureData(DpKit::IDataFileRef trainData)
	{
		trainData_ = trainData;
		return (trainData_ ? S_OK : E_FAIL);
	}


} // namespace Trainer
