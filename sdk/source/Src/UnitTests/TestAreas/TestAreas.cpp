#ifdef _MSC_VER

#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#endif // _MSC_VER

#include <stdio.h>

#include "NetworkImporting/NetworkImportingKit.h"
using namespace NetworkImportingKit;

void EventNotify(const StringA& message, bool newLine = true)
{
	printf(message.c_str());
	if (newLine) printf("\n");
}

// Global Constants 
#define NETWORK_NAME						"TestAreas_001.nlproj"
#define LAYER_FILE_NAME						"Landsat-100000-A3-B40+.pgm"

#define WND_WIDTH							20
#define WND_HEIGHT							20

#define MAP_STEP_X							20
#define MAP_STEP_Y							20

#define AREAS_COUNT							5

int main()
{
	{
		IComponentLoader* piLoader = CConstructTool<CComponentLoader, IComponentLoader>::ConstructObject(IID_IComponentLoader);
		assert(piLoader != NULL);
		
		piLoader->SetLibraryName(StringA("./NetworkImport") + SO_LIB_EXT);
		result resultCode = piLoader->InitializeComponentInstance(CLSID_NetworkImport);
		if (FAILED(resultCode))
		{
			EventNotify("Error: Loading NetworkImport component.");
			EventNotify(StringA("Descr: Library module <NetworkImport") + SO_LIB_EXT + StringA("> not found."));
			EventNotify("Code: result resultCode = piLoader->InitializeComponentInstance(CLSID_NetworkImport);");

			piLoader->Release();

			exit(0);
		}

		IImportManager* piImportManager = NULL;
		resultCode = piLoader->QueryComponentObject(IID_IImportManager, (void**)&piImportManager);
		if (FAILED(resultCode) || !piImportManager)
		{
			EventNotify("Error: Loading NetworkImport component.");
			EventNotify("Descr: Cannot construct object corresponding to <IID_IImportManager> interface.");
			EventNotify("Code: resultCode = piLoader->QueryComponentObject(IID_IImportManager, (void**)&piImportManager);");

			piLoader->Release();		

			exit(0);
		}
		
		resultCode = piImportManager->InitializeManager();
		if (FAILED(resultCode))
		{
			EventNotify("Error: Loading NetworkImport component.");
			EventNotify("Descr: Error during initializing ImportManager object.");
			EventNotify("Code: resultCode = piImportManager->InitializeManager();");

			piImportManager->Release();
			piLoader->Release();

			exit(0);
		}
		
		INetworkProcessor* piNetworkProcessor = NULL;
		resultCode = piImportManager->LoadNLProject(NETWORK_NAME, &piNetworkProcessor);
		if (FAILED(resultCode) || !piNetworkProcessor)
		{
			EventNotify("Error: Loading <TestAreas_001.nlproj> network project.");
			EventNotify("Descr: Error during initializing ImportManager object.");
			EventNotify("Code: resultCode = piImportManager->LoadNLProject(\"TestAreas_001.nlproj\", &piNetworkProcessor);");

			piImportManager->Release();
			piLoader->Release();

			exit(0);
		}

		// Performing experiment
		//////////////////////////////////////////////////////////////////////////
		{
			IPGMBitmap* piLayerBitmap = CConstructTool<CPGMBitmap, IPGMBitmap>::ConstructObject(IID_IPGMBitmap);
			assert(piLayerBitmap != NULL);

			resultCode = piLayerBitmap->LoadPGMBitmap(LAYER_FILE_NAME);
			if (FAILED(resultCode) || !piNetworkProcessor)
			{
				EventNotify("Error: Loading layer bitmap file.");

				piNetworkProcessor->Release();
				piImportManager->Release();
				piLoader->Release();

				exit(0);			
			}

			IDataBitmap* piBitmap = QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(piLayerBitmap, IID_IDataBitmap);
			
			piLayerBitmap->Release();

			EventNotify("Notif: Source bitmap loaded.");

			uint mapWidth = (uint)floor((float)piBitmap->GetWidth() / (float)MAP_STEP_X);
			uint mapHeight = (uint)floor((float)piBitmap->GetHeight() / (float)MAP_STEP_Y);
			uint mapLength = mapWidth * mapHeight;

			IPGMFactory* piAreasFactory[AREAS_COUNT];
			for (uint i = 0;i < AREAS_COUNT;i++)
			{
				piAreasFactory[i] = CConstructTool<CPGMFactory, IPGMFactory>::ConstructObject(IID_IPGMFactory);
				assert(piAreasFactory[i] != NULL);

				IDataFactory* piFactory = NULL;
				piAreasFactory[i]->QueryInterface(IID_IDataFactory, (void**)&piFactory);

				piFactory->CreateFactory(mapLength);

				piFactory->Release();
			}

			IDataFactory* piOutput = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
			piOutput->CreateFactory(AREAS_COUNT);

			IDataFactory* piInput = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
			piInput->CreateFactory(WND_WIDTH * WND_HEIGHT);

			for (uint i = 0;i < mapWidth;i++)
			{
				for (uint j = 0;j < mapHeight;j++)
				{
					printf("Processing bitmap at position: %dx%d...\n", i * MAP_STEP_X, j * MAP_STEP_Y);

					piBitmap->GetDataFactory(i * MAP_STEP_X, j * MAP_STEP_Y, WND_WIDTH, WND_HEIGHT, piInput);

					piNetworkProcessor->SetInputData(piInput);
					piNetworkProcessor->ProcessNetwork();
					piNetworkProcessor->GetOutputData(piOutput);

					for (uint k = 0;k < AREAS_COUNT;k++)
					{
						IDataFactory* piFactory = NULL;
						piAreasFactory[k]->QueryInterface(IID_IDataFactory, (void**)&piFactory);

						piFactory->SetItemData(
							j * mapWidth + i, 
							piOutput->GetItemData(k) * 255);

						printf("%f ", piOutput->GetItemData(k));

						piFactory->Release();
					}
					printf("\n");
				}
			}

			piInput->Release();
			piOutput->Release();

			char destAreaFile[256];
			for (uint i = 0;i < AREAS_COUNT;i++)
			{
				sprintf(destAreaFile, "Area_%d.pgm", i);

				IDataFactory* piFactory = NULL;
				piAreasFactory[i]->QueryInterface(IID_IDataFactory, (void**)&piFactory);

				IPGMBitmap* piTmBitmap = CConstructTool<CPGMBitmap, IPGMBitmap>::ConstructObject(IID_IPGMBitmap); 

				IDataBitmap* piTmDataBitmap = QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(piTmBitmap, IID_IDataBitmap);
				piTmDataBitmap->ConstructFromDataFactory(piFactory, mapWidth, mapHeight);
				piTmDataBitmap->Release();

				piTmBitmap->SavePGMBitmap(destAreaFile);
				piTmBitmap->Release();

				piFactory->Release();
			}

			for (uint i = 0;i < AREAS_COUNT;i++)
				piAreasFactory[i]->Release();

			piBitmap->Release();
		}
		//////////////////////////////////////////////////////////////////////////
		// Experiment done

		// Netwprk unit test
		//////////////////////////////////////////////////////////////////////////
		{
			IDataFactory* piData = CConstructTool<CDataFactory, IDataFactory>::
				ConstructObject(IID_IDataFactory);
			assert(piData != NULL);

			piData->CreateFactory(400);
          
			EventNotify("Processing network...");

			piNetworkProcessor->SetInputData(piData);
			piNetworkProcessor->ProcessNetwork();
			piNetworkProcessor->GetOutputData(piData);

			EventNotify("Network result:");

			for (uint i = 0;i < piData->GetDataLength();i++)
				printf("Output %d: %f\n", i, piData->GetItemData(i));			

			EventNotify("Done.");			

			piData->Release();		
		}
		//////////////////////////////////////////////////////////////////////////
		// Netwprk unit test done
		
		piNetworkProcessor->Release();
		
		piImportManager->Release();     

		piLoader->ReleaseComponentInstance();
		piLoader->Release();
	}

#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif // _MSC_VER

	return 0;
}

