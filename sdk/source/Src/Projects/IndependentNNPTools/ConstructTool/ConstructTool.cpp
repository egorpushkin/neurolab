#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "ConstructToolCmd.h"

using namespace NetworkImportingKit;
using namespace StorageProcessorCommonKit;
using namespace ConsoleHelpersKit;

class ConstructToolApp 
	: public Application
{
	// Forced declaration of assigment operators
	ConstructToolApp(const ConstructToolApp&);
	const ConstructToolApp& operator =(const ConstructToolApp&);

public:
	ConstructToolApp()
		: niHelper_()
		, spHelper_()
		, cfgHelper_(spHelper_)
	{
	}

	virtual result Process()
	{
		if (!cfgHelper_.IsLoaded())
			return E_FAIL;

		// Step 2. Constructing network
		INetworkProcessor* piNetProc = ConstructNetwork();
		if (!piNetProc)
			return E_FAIL;

		// Step 3. Exporting network
		result resultCode = ExportNetwork(piNetProc);
		if (FAILED(resultCode))
		{ }

		// Releasing local config & loacal processor 
		piNetProc->Release();

		return S_OK;
	}

private:
	// Application states machine nodes
	INetworkProcessor* ConstructNetwork()	
	{
		INetworkProcessor* piNetworkProcessor = niHelper_.GetEmptyProcessor();

		IStructureBuilder* piBuilder = 
			QueryTool<INetworkProcessor, IStructureBuilder>::
			QueryInterface(piNetworkProcessor, IID_IStructureBuilder);
        
		IElement* piPrevElement = NULL;
		uint connectionLength = 0;

		ILayersEnumPtr cfgLayers = cfgHelper_.GetLayersEnum();
		for ( bool hasLayer = cfgLayers->SelectFirst() ; hasLayer ; hasLayer = cfgLayers->SelectNext() )
		{
			LayerDataPtr layerData = cfgLayers->GetSelected();

			if ( connectionLength == 0 )
				connectionLength = layerData->neurons_;

			IElement* piCurrentElement = CreateAndCustomizeLayer(
				layerData, 
				connectionLength, 
				piBuilder);

			if ( !piCurrentElement )
			{
				Console::EventNotify(StringA("Error creating element: ") + layerData->layerName_ + StringA("."));				

				piBuilder->Release();
				piNetworkProcessor->Release();

				return NULL;
			}

			if ( piPrevElement )
			{
				piBuilder->ConnectElements(piPrevElement, piCurrentElement, connectionLength);
				piPrevElement->Release();
			}

			if ( layerData->hasBias_ )
			{
				AddBiasInput(
					piCurrentElement, 
					piBuilder);
			}

			connectionLength = layerData->neurons_;

			piPrevElement = piCurrentElement;
			piPrevElement->AddRef();
			piCurrentElement->Release();
		}

		if ( piPrevElement )
			piPrevElement->Release();

		piBuilder->Release();

		return piNetworkProcessor;
	}

	result ExportNetwork(INetworkProcessor* piNetProc)
	{
		StringA projectFile(CommandLine::Instance().GetOperand('o'));
		uint outputFormat = ConstructToolCmd::GetOutputFormat();

		if (outputFormat == FORMAT_SPXML10)
		{
			result resultCode = spHelper_.SerializeNLProject(projectFile, piNetProc, ModeStore);
			if (FAILED(resultCode))
			{
				Console::EventNotify("Error exporting project (FORMAT_SPXML10 method).");
				return resultCode;
			}		
		} else if (outputFormat == FORMAT_DEFBIN10)
		{
			result resultCode = niHelper_.StoreNLProject(projectFile, piNetProc);
			if (FAILED(resultCode))
			{
				Console::EventNotify("Error exporting project (FORMAT_DEFBIN10 method).");
				return resultCode;
			}	
		} else
		{
			Console::EventNotify("Error: Wrong output format for exporting project specified.");
			return E_FAIL;
		}

		return S_OK;
	}

	// Tools
	IElement* CreateAndCustomizeLayer(LayerDataPtr layerData, uint inputsCount, IStructureBuilder* piBuilder)
	{
		IElement* piElement = piBuilder->AddElement(layerData->layerName_);
		if ( !piElement )
			return NULL;

		piBuilder->ApplyTransferFunction(piElement, layerData->transferFunction_);

		ILayerControl* piLayer = QueryTool<IElement, ILayerControl>::QueryInterface(piElement, IID_ILayerControl);
		if ( !piLayer )
		{
			piElement->Release();
			return NULL;
		}

		if ( layerData->hasBias_ )
			++inputsCount;

		piLayer->CreateWeights(inputsCount, layerData->neurons_);
		piLayer->Release();

		return piElement;
	}

	result AddBiasInput(IElement* piElement, IStructureBuilder* piBuilder)
	{
		IElementPtr bias(piBuilder->AddElement(StringA("ConstantInput")));
		if ( !bias )
			return E_FAIL;

		result r = piBuilder->ConnectElements(GetImpl(bias), piElement, 1);

		return r;
	}

private:

	NetworkImportHelper			niHelper_;
	StorageProcessorHelper		spHelper_;
	ConfigHelper				cfgHelper_;

};

int main(int argc, char* const* argv)
{	
	if (FAILED(ConstructToolCmd::Init(argc, argv)))
		return 0;
                       	
	try
	{
		ConstructToolApp application;
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


