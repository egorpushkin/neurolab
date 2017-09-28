#include "../../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "NetworkTrainer.h"

#include "../Log/LogProvider.h"

NetworkTrainer::NetworkTrainer(
	ConsoleHelpersKit::StorageProcessorHelper& spHelper,
	ConsoleHelpersKit::TrainersManagerHelper& tmHelper,
	ConsoleHelpersKit::ConfigHelper& cfgHelper)
	: piNetworkProcessor_(NULL)
	, piTrainData_(NULL)
	, spHelper_(spHelper)
	, tmHelper_(tmHelper)
	, cfgHelper_(cfgHelper)
{
}

NetworkTrainer::~NetworkTrainer()
{
	if ( piNetworkProcessor_ )
		piNetworkProcessor_->Release();
	if ( piTrainData_ )
		piTrainData_->Release();
}
	
result NetworkTrainer::CaptureNetwork(NetworkImportingKit::INetworkProcessor* piNetworkProcessor)
{
	piNetworkProcessor_ = piNetworkProcessor;
	return (piNetworkProcessor_ ? S_OK : E_FAIL);
}

result NetworkTrainer::CaptureData(IDataFile* piTrainData)
{
	piTrainData_ = piTrainData;
	return (piTrainData_ ? S_OK : E_FAIL);
}

NetworkImportingKit::INetworkProcessor* NetworkTrainer::GetNetwork()
{
	piNetworkProcessor_->AddRef();
	return piNetworkProcessor_;
}

result NetworkTrainer::TrainNetwork()
{
	// Get trainer identifier from loaded config
	SpKit::IConfig* piXMLConfig = spHelper_.GetXMLConfig();

	REFCLSID trainerId = piXMLConfig->GetTrainerClsid();

	piXMLConfig->Release();

	// Find required trainer
	TrMngKit::ITrainersManager* piTrainersManager = tmHelper_.GetTrainersManager();

	TrMngKit::ITrainer* piTrainer = piTrainersManager->GetTrainer(trainerId);

	piTrainersManager->Release();

	if ( !piTrainer )
	{
		StringA clsidString;
		StringFromCLSID(&trainerId, clsidString);

		ConsoleHelpersKit::Console::EventNotify("Wrong trainer identifier specified in configuration file.");
		ConsoleHelpersKit::Console::EventNotify(StringA(" Config->Trainer->clsid = ") + clsidString);
		return E_FAIL;
	}

	// Initialize trainer
	piTrainer->AttachNetwork(TrMngKit::PID_PrimaryParam1, piNetworkProcessor_);
	piTrainer->AttachDataObject(TrMngKit::PID_PrimaryParam1, piTrainData_);

	// Setup parameters
	TrMngKit::IProperties* piProperties = NULL;
	result resultCode = piTrainer->QueryInterface(TrMngKit::IID_IProperties, (void**)&piProperties);
	if ( FAILED(resultCode) || !piProperties )
	{
		ConsoleHelpersKit::Console::EventNotify("Error querying TrMngKit::IProperties interface.");

		piTrainer->Release();
		return E_FAIL;
	}

	// Enumerate arguments loaded from configuration file and initialize trainer with them
	SpKit::IArgumentsEnumPtr arguments = cfgHelper_.GetArgumentsEnum();

	for ( bool hasArg = arguments->SelectFirst() ; hasArg ; hasArg = arguments->SelectNext() )
	{
		SpKit::ArgumentsPair argument = arguments->GetSelected();
		piProperties->SetArgument(argument.first, argument.second);
	}

	piProperties->Release();

	// Setup log provider
	LogProvider* pLogProvider = new LogProvider;
	TrMngKit::ILogProvider* piLog = NULL;
	pLogProvider->QueryInterface(TrMngKit::IID_ILogProvider, (void**)&piLog);

	piTrainer->SetLogProvider(piLog);

	piLog->Release();

    // Execute external training procedure
	TrMngKit::IGeneralProcessor* piProcessor = NULL;
	resultCode = piTrainer->QueryInterface(TrMngKit::IID_IGeneralProcessor, (void**)&piProcessor);
	if ( FAILED(resultCode) || !piProcessor )
	{
		ConsoleHelpersKit::Console::EventNotify("Error querying TrMngKit::IGeneralProcessor interface.");

		piTrainer->Release();
		return E_FAIL;
	}

	try
	{
		resultCode = piProcessor->Start();
	}
	catch ( ... )
	{
		ConsoleHelpersKit::Console::EventNotify("Exception caught during ITrainer::Start() execution.");		
	}
	
	piProcessor->Release();
	piTrainer->Release();

	return resultCode;
}
