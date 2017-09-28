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

int main()
{
	{
		IComponentLoader* piLoader = CConstructTool<CComponentLoader, IComponentLoader>
			::ConstructObject(IID_IComponentLoader);
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
		resultCode = piImportManager->LoadNLProject("TestNetwork_001.nlproj", &piNetworkProcessor);
		if (FAILED(resultCode) || !piNetworkProcessor)
		{
			EventNotify("Error: Loading <TestNetwork.nlproj> network project.");
			EventNotify("Descr: Error during initializing ImportManager object.");
			EventNotify("Code: resultCode = piImportManager->LoadNLProject(\"TestNetwork_001.nlproj\", &piNetworkProcessor);");

			piImportManager->Release();
			piLoader->Release();

			exit(0);
		}

		{
			IDataFactory* piData = CConstructTool<CDataFactory, IDataFactory>::
				ConstructObject(IID_IDataFactory);
			assert(piData != NULL);

			piData->CreateFactory(10);
			piData->SetItemData(0, 1.0f);
           
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



