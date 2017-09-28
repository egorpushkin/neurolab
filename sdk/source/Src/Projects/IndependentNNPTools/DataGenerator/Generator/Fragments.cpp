#include "PrecompiledHeader.h"

#include "AreasTool/AreasTool.h"

#include "Fragments.h"

#include "Geometry.h"

#include <Time.h>

namespace Generator
{

	// Public interface
	result Fragments::CutFragments(Workspace::MultispectralImage* pImage, Areas::AreasTool* pAreasTool, uint count, uint width,	uint height, IDataFactory* piInputBand, IDataFactory* piInput, IDataFactory* piOutput, IDataFile* piDataFile)
	{
		for ( uint i = 0 ; i < pAreasTool->GetAreasCount() ; ++i )
		{
			ProcessCutAreaCore(pImage, pAreasTool, i, count, width, height, piInputBand, piInput, piOutput, piDataFile);
		}

        return S_OK;
	}

	// Private interface
	uint Fragments::Random(uint lo, uint hi)
	{
		return (uint)(lo + rand()/(double)RAND_MAX * (hi-lo));		
	}

	result Fragments::MoveFactoryData(IDataFactory* piSourceDataFactory, uint sourceOffset, uint length, IDataFactory* piDestinationDataFactory, uint destinationOffset)
	{
		if ( length == 0 || 
			!piSourceDataFactory->GetData() || 
			!piDestinationDataFactory->GetData() )
			return E_FAIL;

		if ( sourceOffset + length > piSourceDataFactory->GetDataLength() )
			return E_FAIL;

		if ( destinationOffset + length > piDestinationDataFactory->GetDataLength() )
			return E_FAIL;

		memcpy(piDestinationDataFactory->GetData() + destinationOffset, 
			piSourceDataFactory->GetData() + sourceOffset, 
			sizeof(float)*length);

		return S_OK;
	}

	result Fragments::ExportFragmentCore(
		Workspace::MultispectralImage* pImage, 
		uint xOffset, uint yOffset, 
		uint width, uint height, 
		IDataFactory* piInputBand,
		IDataFactory* piInput)
	{
		if ( !pImage || !piInputBand || !piInput )
			return E_FAIL;

		uint i = 0;

		Workspace::IBandsEnumerator* piBandsEnum = pImage->GetBandsEnumerator();
		for ( bool hasBands = piBandsEnum->SelectFirst() ; hasBands ; hasBands = piBandsEnum->SelectNext(), ++i )
		{
			Workspace::Band* pBand = piBandsEnum->GetSelected();

			IPGMBitmap* piPGMBItmap = pBand->GetBitmap();
			IDataBitmap* piDataBitmap = 
				QueryTool<IPGMBitmap, IDataBitmap>::
					QueryInterface(piPGMBItmap, IID_IDataBitmap);
					
			// Receiving singlespectral fragment from the layer
			piDataBitmap->GetDataFactory(xOffset, yOffset, width, height, piInputBand);

			// Mapping read data into prepared buffer
			MoveFactoryData(piInputBand, 0, piInputBand->GetDataLength(), piInput, piInputBand->GetDataLength() * i);
		}
		piBandsEnum->Release();

		return S_OK;
	}

	result Fragments::ProcessCutAreaCore(Workspace::MultispectralImage* pImage, Areas::AreasTool* pAreasTool, uint areaIndex, uint count, uint width, uint height, IDataFactory* piInputBand, IDataFactory* piInput, IDataFactory* piOutput, IDataFile* piDataFile)
	{
		if ( !pImage || !pAreasTool || !piInputBand || !piInput || !piDataFile )
			return E_FAIL;

		uint left, top, right, bottom;
		pAreasTool->GetAreaBoundary(areaIndex, left, top, right, bottom);

		uint exportedFragments = 0;
		while ( exportedFragments < count )
		{
			uint xRand = Random(left, right);
			uint yRand = Random(top, bottom);

			if ( GeometryTool::IsSquareInArea(pAreasTool, areaIndex, xRand, yRand, xRand + width, yRand + height) )
			{
				// Prepare input fragment
				ExportFragmentCore(pImage, xRand, yRand, width, height, piInputBand, piInput);

				// Prepare output fragment
				piOutput->FillFactory(0.0f);
				piOutput->SetItemData(areaIndex, 1.0f);

				// Add fragment to datafile
				piDataFile->AddInputSymbol(piInput);
				piDataFile->AddOutputSymbol(piOutput);

				// Increment a number of grabbed fragments
				++exportedFragments;
			}
		}	

		return S_OK;
	}

}
