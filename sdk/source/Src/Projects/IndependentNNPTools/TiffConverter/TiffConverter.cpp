#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "CommandLine.h"
#include "SerializeDataFactory.h"
#include "SerializeTiffFactory.h"

using namespace NetworkImportingKit;
using namespace StorageProcessorCommonKit;
using namespace ConsoleHelpersKit;

class TiffConverter 
	: public Application
{

	// Forced declaration of assigment operators
	TiffConverter(const TiffConverter&);
	const TiffConverter& operator =(const TiffConverter&);

public:

	TiffConverter()
	{
	}

	virtual result Process()
	{
		// Step 1. Loading input data
		IDataFactory* piInputData = LoadAndVerifyInputData();
		if ( !piInputData )
			return E_FAIL;

/*
		// Step 3. Processing network
		IDataFactory* piOutputData = ProcessNetwork(piNetProc, piInputData);

		// Step 4. Exporting output data
        if ( FAILED(ExportOutputData(piOutputData)) )
		{ }

		// Release local objects
		piOutputData->Release();
		piNetProc->Release(); */
		piInputData->Release();

		return S_OK;
	}

private:
	// Application states machine nodes
	IDataFactory* LoadAndVerifyInputData()
	{
		// Load data buffer
		StringA dataFile(CommandLine::Instance().GetOperand('i'));

		IDataFactory* piInputData = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);

		result r = SerializeTiffFactory::Serialize(dataFile, piInputData, ModeLoad);

		if ( FAILED(r) )
		{
			Console::EventNotify(StringA("Error loading input data file: ") + dataFile + StringA("."));
			return NULL;
		}

        return piInputData;
	}

/*	result ExportOutputData(IDataFactory* piOutputData)
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
	} */

private:



};

int main(int argc, char* const* argv)
{	
	if (FAILED(CmdProc::Init(argc, argv)))
		return 0;

	try
	{
		TiffConverter application;
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


