#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "ProjectConverterCmd.h"

using namespace NetworkImportingKit;
using namespace ConsoleHelpersKit;

class ProjectConverter 
	: public Application
{
public:
	virtual result Process()
	{
		StringA sourceFileName(CommandLine::Instance().GetOperand('s'));
		StringA destinationFileName(CommandLine::Instance().GetOperand('d'));

		uint convertionMethod = ProjectConverterCmd::GetConversionMethod();

		if (convertionMethod == CONV_SPXML10_TO_DEFBIN10)
		{
			// Receiving processor control interface
			INetworkProcessor* piNetworkProcessor = niHelper_.GetEmptyProcessor();
			
			// Loaiding project data (from xml project file)
			result resultCode = spHelper_.SerializeNLProject(sourceFileName, piNetworkProcessor, ModeLoad);
			if (FAILED(resultCode))
			{
				Console::EventNotify("Serialization error (during load procedure).");
				return E_FAIL;
			}

			// Store project data (to binary project file)
			resultCode = niHelper_.StoreNLProject(destinationFileName, piNetworkProcessor);
			if (FAILED(resultCode))
			{
				piNetworkProcessor->Release();

				Console::EventNotify("Serialization error (during store procedure).");
				return E_FAIL;
			}
			
			// Release local copy of processor
			piNetworkProcessor->Release();

		} else if (convertionMethod == CONV_DEFBIN10_TO_SPXML10)
		{
			INetworkProcessor* piNetworkProcessor = NULL;

			// Loading project data (from binary project file)
			result resultCode = niHelper_.LoadNLProject(sourceFileName, &piNetworkProcessor);
			if (FAILED(resultCode) || !piNetworkProcessor)
			{
				Console::EventNotify("Serialization error (during load procedure).");
				return E_FAIL;		
			}		

			// Store project data (to xml project file)
			resultCode = spHelper_.SerializeNLProject(destinationFileName, piNetworkProcessor, ModeStore);
			if (FAILED(resultCode))
			{
				piNetworkProcessor->Release();

				Console::EventNotify("Serialization error (during store procedure).");
				return E_FAIL;				
			}            

			// Release local copy of processor
			piNetworkProcessor->Release();

		} else
		{
			Console::EventNotify("Error: Wrong converting method specified.");
			return E_FAIL;
		}

		return S_OK;
	}

private:
	NetworkImportHelper			niHelper_;
	StorageProcessorHelper		spHelper_;
};

int main(int argc, char* const* argv)
{	
	if (FAILED(ProjectConverterCmd::Init(argc, argv)))
		return 0;	

	try
	{
		ProjectConverter application;
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


