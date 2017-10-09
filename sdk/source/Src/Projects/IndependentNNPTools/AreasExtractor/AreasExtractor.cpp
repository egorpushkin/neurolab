#include "PrecompiledHeader.h"

#include "AreasExtractorCmd.h"

#include "LogProvider.h"

#include "Serialization/XMLProjectParser.h"

using namespace ConsoleHelpersKit;
using namespace TrainersManagerKit;
using namespace Workspace;
using namespace Serialization;

// {28316e04-d47d-49d4-8e02-b198fe04d099} 
DEFINE_GUID(CLSID_Clustering, 
0x28316e04, 0xd47d, 0x49d4, 0x8e, 0x02, 0xb1, 0x98, 0xfe, 0x04, 0xd0, 0x99);

class AreasExtractor
	: public Application
{
	// Forced declaration of assignment operators
	AreasExtractor(const AreasExtractor&);
	const AreasExtractor& operator =(const AreasExtractor&);

public:
	AreasExtractor()
		: tmHelper_()
		, areasProject_(new AreasProject, IID_IAreasProject)
		, clustering_()
		, dataObject1_(new CDataFile, IID_IDataFile)
		, dataObject2_(new CDataFile, IID_IDataFile)
	{
		if ( !areasProject_ )
			throw ConsoleException("Error initialization AreasProject engine.");
	}

	virtual result Process()
	{
		StringA projectFile(CommandLine::Instance().GetOperand('p'));

		XMLProjectParser parser;
		if ( FAILED(parser.LoadProject(projectFile, GetImpl(areasProject_))) )
		{
			Console::EventNotify(StringA("Error loading areas project file: ") + projectFile + StringA("."));
			return E_FAIL;
		}

		clustering_ = tmHelper_.GetTrainersManager()->GetTrainer(CLSID_Clustering);
		if ( !clustering_ )
		{
			ConsoleHelpersKit::Console::EventNotify("Areas Detector trainer can not be loaded.");
			return E_FAIL;
		}

		ILogProviderPtr logProvider(new LogProvider, IID_ILogProvider);
		clustering_->SetLogProvider(GetImpl(logProvider));

		if ( FAILED(ClusterImage()) )
		{
			ConsoleHelpersKit::Console::EventNotify("Clustering failed.");
			return E_FAIL;
		}

		if ( FAILED(ExportResults()) )
		{
			ConsoleHelpersKit::Console::EventNotify("Failed to export clustering results.");
			return E_FAIL;
		}

		return S_OK;
	}

private:
	// Application states machine nodes
	result ClusterImage()
	{
		SetupParameters();
		
		SetupDataObjects();

		IGeneralProcessorPtr processor(clustering_, IID_IGeneralProcessor);
		
		if ( FAILED(processor->Start()) )
			return E_FAIL;

		return S_OK;
	}

	result ExportResults()
	{
		// Export clusters map
		StringA mapFile(CommandLine::Instance().GetOperand('m'));

        IPGMBitmapPtr pgmBitmap(new CPGMBitmap, IID_IPGMBitmap);
		IDataBitmapPtr dataBuffer(pgmBitmap, IID_IDataBitmap);

		uint mapIndex = dataObject1_->GetOutputSymbolsCount() - 1;
		dataBuffer->ConstructFromDataFactory(
			dataObject1_->GetOutputSymbol(mapIndex), 
			areasProject_->GetMultispecImage()->GetWidth(),
			areasProject_->GetMultispecImage()->GetHeight());

		pgmBitmap->SavePGMBitmap(mapFile.c_str());

		// Export boundaries
		

		return S_OK;
	}

	// Tools 
	result SetupParameters()
	{
		IPropertiesPtr properties(clustering_, IID_IProperties);

		MinCOM::CommonVariant varParam;
		varParam.vt_ = CE_UINT;
		varParam.uintVal_ = areasProject_->GetMultispecImage()->GetWidth();
		properties->SetArgument("Width", varParam);

		varParam.uintVal_ = areasProject_->GetMultispecImage()->GetHeight();
		properties->SetArgument("Height", varParam);

		varParam.uintVal_ = areasProject_->GetMapConfig()->GetUintParameter("Scale");
		properties->SetArgument("Scale", varParam);

		varParam.uintVal_ = areasProject_->GetMapConfig()->GetUintParameter("ClustersCount");
		properties->SetArgument("ClustersCount", varParam);

		return S_OK;
	}

	result SetupDataObjects()
	{
		uint length = 
			areasProject_->GetMultispecImage()->GetWidth() * 
			areasProject_->GetMultispecImage()->GetHeight();

		dataObject1_->CreateNewFile(length, length);

		IDataFactoryPtr buffer(new CDataFactory, IID_IDataFactory);

		IBandsEnumerator* piBandsEnum = areasProject_->GetMultispecImage()->GetBandsEnumerator();
		for ( bool hasBands = piBandsEnum->SelectFirst() ; hasBands ; hasBands = piBandsEnum->SelectNext() )
		{
			Band* pBand = piBandsEnum->GetSelected();

			IDataBitmapPtr bitmap(pBand->GetBitmap(), IID_IDataBitmap);

			bitmap->GetDataFactory(
				0,
				0, 
				bitmap->GetWidth(),
				bitmap->GetHeight(),
				GetImpl(buffer));

			dataObject1_->AddInputSymbol(GetImpl(buffer));
		}
		piBandsEnum->Release();

		clustering_->AttachDataObject(PID_PrimaryParam1, GetImpl(dataObject1_));
		clustering_->AttachDataObject(PID_PrimaryParam2, GetImpl(dataObject2_));

		return S_OK;
	}

private:
	TrainersManagerHelper		tmHelper_;

	IAreasProjectPtr			areasProject_;
	ITrainerPtr					clustering_;

	IDataFilePtr				dataObject1_;
	IDataFilePtr				dataObject2_;

};

int main(int argc, char* const* argv)
{	
	if ( FAILED(AreasExtractorCmd::Init(argc, argv)) )
		return 0;

	try
	{
		AreasExtractor application;
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

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}


