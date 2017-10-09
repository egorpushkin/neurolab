#include "PrecompiledHeader.h"

#include "AreasTool/AreasTool.h"

#include "Generator.h"

#include "Fragments.h"

namespace Generator
{

	TrainDataGenerator::TrainDataGenerator()
	{
	}

	TrainDataGenerator::~TrainDataGenerator()
	{
	}

	// Public interface
	result TrainDataGenerator::Generate(Workspace::IAreasProject* piProject, Areas::AreasTool* pAreas, IDataFile* piDataFile)
	{
		if ( !piProject || !pAreas || !piDataFile )
			return S_OK;

		uint dataSamplesPerArea = piProject->GetMapConfig()->GetUintParameter("data_samples");
		if ( !dataSamplesPerArea )
			return E_FAIL;

        uint width = piProject->GetMapConfig()->GetUintParameter("wnd_width");
		uint height = piProject->GetMapConfig()->GetUintParameter("wnd_height");

        if ( !width || !height )
			return E_FAIL;

		StringA order;
		piProject->GetMapConfig()->GetParameter("samples_order", order);

		if ( order.size() == 0 || 
			( order != "normal" && order != "alternate" ) )
			order = "normal";

		// Configure data file object
		uint bandLength = 
			// A number of bytes per band
			width * height; 

		uint inputLength = 
			// A number of bytes per input fragment
			bandLength * piProject->GetMultispecImage()->GetBandsCount();

		uint outputLength = 
			// A number of classes (a number of actual areas)
			(uint)pAreas->GetAreasCount();

		piDataFile->CreateNewFile(inputLength, outputLength);

		// Create temporary input and output objects
		IDataFactory* piInputBand = 
			CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piInputBand->CreateFactory(bandLength, 0.0f);

		IDataFactory* piInput = 
			CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piInput->CreateFactory(inputLength, 0.0f);

		IDataFactory* piOutput = 
			CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piOutput->CreateFactory(outputLength, 0.0f);

		// Data file generation
		if ( order == "normal" )
		{
			Fragments::CutFragments(
				piProject->GetMultispecImage(), 
				pAreas,
				dataSamplesPerArea, 
				width, height, 
				piInputBand, piInput, piOutput, 
				piDataFile);
		}
		else if ( order == "alternate" )
		{
			for ( uint i = 0 ; i < dataSamplesPerArea ; ++i )
			{
				Fragments::CutFragments(
					piProject->GetMultispecImage(), 
					pAreas,
					1, // Add just one fragment for each area via approach
					width, height, 
					piInputBand, piInput, piOutput, 
					piDataFile);
			}
		}

		// Adjust datafile content
		float multiplier = piProject->GetMapConfig()->GetFloatParameter("sp_scale");
		if ( multiplier == 0.0 )
			multiplier = 1.0;

		for ( uint i = 0 ; i < piDataFile->GetInputSymbolsCount() ; ++i )
		{
			for ( uint j = 0 ; j < piDataFile->GetInputSymbolLength() ; ++j )
			{
				float value = piDataFile->GetInputSymbol(i)->GetItemData(j) * multiplier;
				piDataFile->GetInputSymbol(i)->SetItemData(j, value);
			}
		}
		
		// Releasing temporary objects
		piInputBand->Release();
		piInput->Release();
		piOutput->Release();

		return S_OK;
	}

}
