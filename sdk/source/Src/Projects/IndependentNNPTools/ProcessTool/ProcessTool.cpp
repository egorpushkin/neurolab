#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "ProcessToolCmd.h"
#include "SerializeDataFactory.h"
#include "SerializeTiffFactory.h"

using namespace NetworkImportingKit;
using namespace StorageProcessorCommonKit;
using namespace ConsoleHelpersKit;

class ProcessTool 
	: public Application
{
	// Forced declaration of assigment operators
	ProcessTool(const ProcessTool&);
	const ProcessTool& operator =(const ProcessTool&);

public:
	ProcessTool()
		: niHelper_()
		, spHelper_()
		, cfgHelper_(spHelper_)
	{
	}

	virtual result Process()
	{
		if (!cfgHelper_.IsLoaded())
			return E_FAIL;

		// Step 1. Loading network
		INetworkProcessor* piNetProc = LoadNetwork();
		if ( !piNetProc )
			return E_FAIL;

		// Step 2. Loading input data
		IDataFactory* piInputData = LoadAndVerifyInputData(piNetProc);
		if ( !piInputData )
		{
			piNetProc->Release();
			return E_FAIL;
		}

		// Step 3. Processing network
		IDataFactory* piOutputData = ProcessNetwork(piNetProc, piInputData);

		// Step 4. Exporting output data
        if ( FAILED(ExportOutputData(piOutputData)) )
		{ }

		// Release local objects
		piOutputData->Release();
		piNetProc->Release();
		piInputData->Release();

		return S_OK;
	}

private:
	// Application states machine nodes
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

	IDataFactory* LoadAndVerifyInputData(INetworkProcessor* piNetProc)
	{
		// Load data buffer
		StringA dataFile(CommandLine::Instance().GetOperand('i'));

		IDataFactory* piInputData = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);

		result r = S_OK;
			
		if ( ProcessToolCmd::GetDataFormat() == DATA_FORMAT_PLAIN_TEXT )
		{
			r = SerializeDataFactory::Serialize(dataFile, piInputData, ModeLoad);
		} 
		else if ( ProcessToolCmd::GetDataFormat() == DATA_FORMAT_TIFF )
		{
			r = SerializeTiffFactory::Serialize(dataFile, piInputData, ModeLoad);
		}

		if ( FAILED(r) )
		{
			Console::EventNotify(StringA("Error loading input data file: ") + dataFile + StringA("."));
			return NULL;
		}

		// Check data correspondence to loaded network
		IElementsCollection* piElements = 
			QueryTool<INetworkProcessor, IElementsCollection>::
				QueryInterface(piNetProc, IID_IElementsCollection);

		if ( piElements->GetInputsCount() != piInputData->GetDataLength() )
		{
			Console::EventNotify("Wrong data buffer loaded.");
			piElements->Release();
			return NULL;
		}

		piElements->Release();

        return piInputData;
	}

	IDataFactory* ProcessNetwork(INetworkProcessor* piNetProc, IDataFactory* piInputData)
	{
		// Determine a number of network outputs (classes count)
		IElementsCollection* piElements = 
			QueryTool<INetworkProcessor, IElementsCollection>::
				QueryInterface(piNetProc, IID_IElementsCollection);

		uint classesCount = piElements->GetOutputsCount();

		piElements->Release();

		// Create temporary buffer to store network output
		IDataFactory* piOutputData = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piOutputData->CreateFactory(classesCount);

		// Processing network
		piNetProc->SetInputData(piInputData);
		piNetProc->ProcessNetwork();
		piNetProc->GetOutputData(piOutputData);

		return piOutputData;
	}

	result ExportOutputData(IDataFactory* piOutputData)
	{
		StringA dataFile(CommandLine::Instance().GetOperand('o'));

		result r = S_OK;
			
		if ( ProcessToolCmd::GetDataFormat() == DATA_FORMAT_PLAIN_TEXT )
		{
			r = SerializeDataFactory::Serialize(dataFile, piOutputData, ModeStore);
		} 
		else if ( ProcessToolCmd::GetDataFormat() == DATA_FORMAT_TIFF )
		{
			r = SerializeTiffFactory::Serialize(dataFile, piOutputData, ModeStore);
		}

		if ( FAILED(r) )
		{
			Console::EventNotify(StringA("Error saving output data to file: ") + dataFile + StringA("."));
			return E_FAIL;
		}

		return S_OK;
	}

private:
	NetworkImportHelper			niHelper_;
	StorageProcessorHelper		spHelper_;
	ConfigHelper				cfgHelper_;
};

int main(int argc, char* const* argv)
{	
	if (FAILED(ProcessToolCmd::Init(argc, argv)))
		return 0;

	try
	{
		ProcessTool application;
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


