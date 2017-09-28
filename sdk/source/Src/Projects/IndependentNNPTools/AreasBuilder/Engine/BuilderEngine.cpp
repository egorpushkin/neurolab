#include "../PrecompiledHeader.h"

#include "BuilderEngine.h"

using namespace ConsoleHelpersKit;
using namespace Workspace;
using namespace NetworkImportingKit;

namespace BuilderEngine
{

result BuildAeras(IAreasProject* piAreasProject)
{
	// Step Initial. Receiving required controls
	INetworkProcessor* piNetProc = piAreasProject->GetNetworkProject()->GetProcessor();
	IElementsCollection* piNetElements = QueryTool<INetworkProcessor, IElementsCollection>::
		QueryInterface(piNetProc, IID_IElementsCollection);

	uint classesCount = piNetElements->GetOutputsCount();	
	uint inputVectorLength = piNetElements->GetInputsCount();

	uint wndWidth = piAreasProject->GetMapConfig()->GetUintParameter("wnd_width");
	uint wndHeight = piAreasProject->GetMapConfig()->GetUintParameter("wnd_height");
	uint wndLength = wndWidth * wndHeight;
	uint xStep = piAreasProject->GetMapConfig()->GetUintParameter("x_step");
	uint yStep = piAreasProject->GetMapConfig()->GetUintParameter("y_step");	

	float spectralScale = piAreasProject->GetMapConfig()->GetFloatParameter("sp_scale");	

	uint imageWidth = piAreasProject->GetMultispecImage()->GetWidth();
	uint imageHeight = piAreasProject->GetMultispecImage()->GetHeight();

	uint mapWidth = (uint)(floor(imageWidth * 1.0 / xStep) - floor(wndWidth * 1.0 / xStep) + 1);
	uint mapHeight = (uint)(floor(imageHeight * 1.0 / yStep) - floor(wndHeight * 1.0 / yStep) + 1);
	uint mapLength = mapWidth * mapHeight;

	piAreasProject->GetAreasHolder()->SetMapDetails(mapWidth, mapHeight);

	// Step 1. Creating areas
	for (uint i = 0;i < classesCount;i++)
	{
		IDataFactory* piFactory = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piFactory->CreateFactory(mapLength, 0.3f);
		piAreasProject->GetAreasHolder()->AddArea(piFactory);
		piFactory->Release();
	}

	// Step 2. Preparing temporary objects
	IDataFactory* piInput = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piInput->CreateFactory(inputVectorLength);

	IDataFactory* piOutput = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piOutput->CreateFactory(classesCount);
	
	IDataFactory* piBandBlock = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piOutput->CreateFactory(wndLength);

	// Step 3. Building areas
	uint mapIndex = 0;

	Console::EventNotify("Areas building stared...");
		
	for (uint j = 0;j < mapHeight;j++)	
	{
		for (uint i = 0;i < mapWidth;i++)
		{
			IBandsEnumerator* piBandsEnum = piAreasProject->GetMultispecImage()->GetBandsEnumerator();
			uint k = 0;
			for (bool hasBands = piBandsEnum->SelectFirst();hasBands;hasBands = piBandsEnum->SelectNext())
			{	
				// Prepare band fragment
				Band* pBand = piBandsEnum->GetSelected();

				IPGMBitmap* piPGMBand = pBand->GetBitmap();
				IDataBitmap* piRawBand = QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(piPGMBand, IID_IDataBitmap);

				piRawBand->GetDataFactory(i * xStep, j * yStep, wndWidth, wndHeight, piBandBlock);

				piRawBand->Release();
				piPGMBand->Release();

				// Prepare input data 
				memcpy(
					piInput->GetData() + k * wndLength, 
					piBandBlock->GetData(),
					wndLength * sizeof(float));

				++k;
			}
			piBandsEnum->Release();

			for ( uint k = 0 ; k < piInput->GetDataLength() ; ++k )
			{
				float value = piInput->GetItemData(k) * spectralScale;
				piInput->SetItemData(k, value);
			}

			piNetProc->SetInputData(piInput);
			piNetProc->ProcessNetwork();
			piNetProc->GetOutputData(piOutput);

			for (uint k = 0;k < classesCount;k++)
				piAreasProject->GetAreasHolder()->GetArea(k)->SetItemData(
					j * mapWidth + i, 
					piOutput->GetItemData(k));

			++mapIndex;

			// Messaging
			//////////////////////////////////////////////////////////////////////////
			char position[MAX_PATH];
            sprintf(position, "%d x %d", i * xStep, j * yStep);

			StringA message = 
				StringA("Processing bitmap at position: ") + 
				StringA(position);
			Console::EventNotify(message);
		}
	}

	Console::EventNotify("Areas building done.");

	// Step 4. Release temporary objects
	piInput->Release();
    piOutput->Release();
	piBandBlock->Release();
	
	// Step Final. Release controls
	piNetElements->Release();
    piNetProc->Release();

	piAreasProject->SetBuilt();

	return S_OK;
}

}
