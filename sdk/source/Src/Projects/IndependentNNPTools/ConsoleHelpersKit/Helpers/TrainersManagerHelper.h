//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: TrainersManagerHelper.h
//	Description: TrainersManagerHelper declaration and implementation.  

#ifndef TRAINERSMANAGERHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
#define TRAINERSMANAGERHELPER_H__CONSOLEHELPERSKIT__INCLUDED_

class TrainersManagerHelper
{
public:
	TrainersManagerHelper()
		: piLoader_(NULL)
		, piTrainersManager_(NULL)
	{
		piLoader_ = CConstructTool<CComponentLoader, IComponentLoader>
			::ConstructObject(IID_IComponentLoader);
		assert(piLoader_ != NULL);

		piLoader_->SetLibraryName(StringA("./TrainersManager") + SO_LIB_EXT);
		result resultCode = piLoader_->InitializeComponentInstance(TrMngKit::CLSID_TrainersManager);
		if (FAILED(resultCode))
		{
			Console::EventNotify("Error: Loading TrainersManager component.");
			Console::EventNotify(StringA("Descr: Library module <TrainersManager") + SO_LIB_EXT + StringA("> not found."));
			Console::EventNotify("Code: result resultCode = piLoader_->InitializeComponentInstance(CLSID_TrainersManager);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}
		
		resultCode = piLoader_->QueryComponentObject(TrMngKit::IID_ITrainersManager, (void**)&piTrainersManager_);
		if (FAILED(resultCode) || !piTrainersManager_)
		{
			Console::EventNotify("Error: Loading TrainersManager component.");
			Console::EventNotify("Descr: Cannot construct object corresponding to <IID_ITrainersManager> interface.");
			Console::EventNotify("Code: resultCode = piLoader_->QueryComponentObject(IID_ITrainersManager, (void**)&piTrainersManager_);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

		TrMngKit::ITrainersLoader* piTrainersLoader = NULL;
		resultCode = piLoader_->QueryComponentObject(TrMngKit::IID_ITrainersLoader, (void**)&piTrainersLoader);
		
		piTrainersLoader->SetArgumentName(TrMngKit::LOADER_PARAM_DIR_NAME, StringA("Trainers"));	

		piTrainersManager_->SetLoader(piTrainersLoader);
		resultCode = piTrainersManager_->LoadTrainers();
		if (FAILED(resultCode))
		{
			Console::EventNotify("Error: Failed to load trainers.");
			Console::EventNotify("Descr: Error during initializing TrainersManager object.");
			Console::EventNotify("Code: resultCode = piTrainersManager_->LoadTrainers();");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

		piTrainersLoader->Release();
	}

	virtual ~TrainersManagerHelper()
	{
		CleanUp();
	}

	// Public interface
	//////////////////////////////////////////////////////////////////////////
	TrMngKit::ITrainersManager* GetTrainersManager()
	{
		if (!piTrainersManager_)
			throw ConsoleException("TrainersManagerHelper was not properly initialized.");

		piTrainersManager_->AddRef();	
        return piTrainersManager_;
	}

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	void CleanUp()
	{
		if (piTrainersManager_)
			piTrainersManager_->Release();
		if (piLoader_)
			piLoader_->Release();
		
		piLoader_ = NULL;
		piTrainersManager_ = NULL;
	}

	// Members
	//////////////////////////////////////////////////////////////////////////
	IComponentLoader*								piLoader_;
	TrMngKit::ITrainersManager*						piTrainersManager_;

};

#endif // !TRAINERSMANAGERHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
