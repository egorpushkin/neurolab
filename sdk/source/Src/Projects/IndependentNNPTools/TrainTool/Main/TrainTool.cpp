#include "../../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "TrainToolCmd.h"

#include "../Storage/SerializeTrainData.h"
#include "../Trainer/NetworkTrainer.h"

using namespace NetworkImportingKit;
using namespace StorageProcessorCommonKit;
using namespace ConsoleHelpersKit;
using namespace TrainersManagerKit;

class TrainTool 
	: public Application
{
	// Forced declaration of assignment operators
	TrainTool(const TrainTool&);
	const TrainTool& operator =(const TrainTool&);

public:
	TrainTool()
		: niHelper_()
		, spHelper_()
		, tmHelper_()
		, cfgHelper_(spHelper_)
		, networkTrainer_(spHelper_, tmHelper_, cfgHelper_)
	{
	}

	virtual result Process()
	{
		if ( !cfgHelper_.IsLoaded() )
			return E_FAIL;

		// Step 1. Loading training data set
		if ( FAILED(networkTrainer_.CaptureData(LoadAndVerifyTrainData())) )
			return E_FAIL;

		// Step 2. Loading network
		if ( FAILED(networkTrainer_.CaptureNetwork(LoadNetwork())) )
			return E_FAIL;

		// Step 3. Configuring network
		if ( FAILED(ConfigureNetwork()) )
            return E_FAIL;

		// Step 4. Exporting network
		if ( FAILED(StoreNetwork()) )
		{ }

		return S_OK;
	}

private:
	// Application states machine nodes
	IDataFile* LoadAndVerifyTrainData()
	{
		StringA dataFile(CommandLine::Instance().GetOperand('d'));

		IDataFile* piTrainData = NULL;
		result resultCode = TrainDataSerializer::LoadData(dataFile, &piTrainData);
		if ( FAILED(resultCode) || !piTrainData )
		{
			Console::EventNotify(StringA("Error loading data file: ") + dataFile + StringA("."));
			return NULL;
		}

        return piTrainData;
	}

	INetworkProcessor* LoadNetwork()	
	{
		StringA projectFile(CommandLine::Instance().GetOperand('n'));
		
		INetworkProcessor* piNetworkProcessor = niHelper_.GetEmptyProcessor();

		result resultCode = spHelper_.SerializeNLProject(projectFile, piNetworkProcessor, ModeLoad);
		if (FAILED(resultCode))
		{
			Console::EventNotify(StringA("Error loading network project file: ") + projectFile + StringA("."));
			piNetworkProcessor->Release();
			return NULL;
		}	

		return piNetworkProcessor;
	}

	result ConfigureNetwork()
	{		
		return networkTrainer_.TrainNetwork();	
	}

	result StoreNetwork()	
	{
		INetworkProcessor* piNetworkProcessor = networkTrainer_.GetNetwork();

		StringA projectFile(CommandLine::Instance().GetOperand('n'));

		result resultCode = spHelper_.SerializeNLProject(projectFile, piNetworkProcessor, ModeStore);

		piNetworkProcessor->Release();

		if (FAILED(resultCode))
		{
			Console::EventNotify(StringA("Error writing network project file to: ") + projectFile + StringA("."));
			return E_FAIL;
		}	

		return S_OK;
	}

private:
	NetworkImportHelper			niHelper_;
	StorageProcessorHelper		spHelper_;
	TrainersManagerHelper		tmHelper_;
	ConfigHelper				cfgHelper_;

	NetworkTrainer				networkTrainer_;
};

int main(int argc, char* const* argv)
{	
	if (FAILED(TrainToolCmd::Init(argc, argv)))
		return 0;

	try
	{
		TrainTool application;
		application.Process();
	} 
	catch (exception& ex)
	{
		Console::EventNotify("Abnormal program termination caused by the following reason:");
		Console::EventNotify(ex.what());
	}
	catch (...)
	{
		Console::EventNotify("Abnormal program termination caused by unknown reason.");
	}

	CommandLineDeleter::GracefulDelete();

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}


