// TrMngTest01.cpp : Defines the entry point for the console application.
//

#ifdef _MSC_VER

#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#endif // _MSC_VER

#include <tchar.h>
#include <iostream>

#include "TrainersManager/TrainersManagerKit.h"
using namespace TrainersManagerKit;


int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	{

		IComponentLoader* piLoader = CConstructTool<CComponentLoader, IComponentLoader>
			::ConstructObject(IID_IComponentLoader);
		assert(piLoader != NULL);

		piLoader->SetLibraryName(StringA("./TrainersManager") + SO_LIB_EXT);
		result resultCode = piLoader->InitializeComponentInstance(CLSID_TrainersManager);

		ITrainersLoader* piTrainersLoader = NULL;
		resultCode = piLoader->QueryComponentObject(IID_ITrainersLoader, (void**)&piTrainersLoader);
		piTrainersLoader->SetArgumentName(LOADER_PARAM_DIR_NAME, "Trainers");	

		ITrainersManager* piTrainersManager = NULL;
		resultCode = piLoader->QueryComponentObject(IID_ITrainersManager, (void**)&piTrainersManager);

		piTrainersManager->SetLoader(piTrainersLoader);
		piTrainersManager->LoadTrainers();

        piTrainersLoader->Release();

		{

			// Test 1. Enumerating trainers
			//////////////////////////////////////////////////////////////////////////
			cout << "Test 1. Trainers list:" << endl;

			ITrainersEnum* piTrainersEnum = piTrainersManager->GetTrainersEnum();
			for (bool hasTrainers = piTrainersEnum->SelectFirst();hasTrainers;hasTrainers = piTrainersEnum->SelectNext())
			{
				ITrainer* piTrainer = piTrainersEnum->GetSelected();

				TRAINER_INFO trInfo;
				piTrainer->GetTrainerInfo(&trInfo);

				cout << " Trainer info:" << endl;
				cout << " Name: " << trInfo.name_ << endl;
				cout << " Title: " << trInfo.title_ << endl;
				cout << " Version: " << trInfo.version_.version_ << endl;
			}
			piTrainersEnum->Release();

			// Test 2. Trainer location by clsid
			//////////////////////////////////////////////////////////////////////////
			cout << "Test 2. Trainer Location by clsid:" << endl;

			// {dddb35e4-ae9d-4196-8324-9ed619517b1b} 
			DEFINE_GUID(CLSID_RGFTrainer, 
			0xdddb35e4, 0xae9d, 0x4196, 0x83, 0x24, 0x9e, 0xd6, 0x19, 0x51, 0x7b, 0x1b);

			ITrainer* piRBFTrainer = piTrainersManager->GetTrainer(CLSID_RGFTrainer);
			if (piRBFTrainer)
			{
				cout << " Trainer found!" << endl;

				piRBFTrainer->Release();
			} else
			{
				cout << " Trainer not found!" << endl;
			}	

			// Test 3. Trainer location by name
			//////////////////////////////////////////////////////////////////////////
			cout << "Test 3. Trainer Location by name:" << endl;

			piRBFTrainer = piTrainersManager->GetTrainer(StringA("RBFStandardDeviation"));
			if (piRBFTrainer)
			{
				cout << " Trainer found!" << endl;

				piRBFTrainer->Release();
			} else
			{
				cout << " Trainer not found!" << endl;
			}	

			// Test 4. Trainer location by name
			//////////////////////////////////////////////////////////////////////////
			cout << "Test 4. Trainer Location by name (must not be found):" << endl;

			piRBFTrainer = piTrainersManager->GetTrainer(StringA("RBFStandardDeviation XXX"));
			if (piRBFTrainer)
			{
				cout << " Trainer found!" << endl;

				piRBFTrainer->Release();
			} else
			{
				cout << " Trainer not found!" << endl;
			}	
			
			// Test G. Guids
			//////////////////////////////////////////////////////////////////////////		
			StringA str;
			StringFromCLSID(&CLSID_RGFTrainer, str);
			
			cout << "Test 4. Guids" << endl;
			cout << " FromCLSID " << str.c_str() << endl;

			CLSID idRev;
			CLSIDFromString(str, &idRev);
			StringFromCLSID(&idRev, str);

			cout << " 2 step " << str.c_str() << endl;		
			
		}	
		
		piTrainersManager->Release();

		piLoader->Release();

	}


#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif // _MSC_VER

	return 0;
}

