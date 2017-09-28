//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: NetworkImportHelper.h
//	Description: NetworkImportHelper declaration and implementation.  

#ifndef NETWORKIMPORTHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
#define NETWORKIMPORTHELPER_H__CONSOLEHELPERSKIT__INCLUDED_

class NetworkImportHelper
{
public:
	NetworkImportHelper()
		: piLoader_(NULL)
		, piImportManager_(NULL)
	{
		piLoader_ = CConstructTool<CComponentLoader, IComponentLoader>
			::ConstructObject(IID_IComponentLoader);
		assert(piLoader_ != NULL);

		piLoader_->SetLibraryName(StringA("./NetworkImport") + SO_LIB_EXT);
		result resultCode = piLoader_->InitializeComponentInstance(NetworkImportingKit::CLSID_NetworkImport);
		if (FAILED(resultCode))
		{
			Console::EventNotify("Error: Loading NetworkImport component.");
			Console::EventNotify(StringA("Descr: Library module <NetworkImport") + SO_LIB_EXT + StringA("> not found."));
			Console::EventNotify("Code: result resultCode = piLoader_->InitializeComponentInstance(CLSID_NetworkImport);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}
		
		resultCode = piLoader_->QueryComponentObject(NetworkImportingKit::IID_IImportManager, (void**)&piImportManager_);
		if (FAILED(resultCode) || !piImportManager_)
		{
			Console::EventNotify("Error: Loading NetworkImport component.");
			Console::EventNotify("Descr: Cannot construct object corresponding to <IID_IImportManager> interface.");
			Console::EventNotify("Code: resultCode = piLoader_->QueryComponentObject(IID_IImportManager, (void**)&piImportManager);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

		resultCode = piImportManager_->InitializeManager();
		if (FAILED(resultCode))
		{
			Console::EventNotify("Error: Loading NetworkImport component.");
			Console::EventNotify("Descr: Error during initializing ImportManager object.");
			Console::EventNotify("Code: resultCode = piImportManager_->InitializeManager();");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}
	}

	virtual ~NetworkImportHelper()
	{
		CleanUp();
	}

	// Public interface
	//////////////////////////////////////////////////////////////////////////
	NetworkImportingKit::INetworkProcessor* GetEmptyProcessor()
	{
		if (!piImportManager_)
			throw ConsoleException("NetworkImportHelper was not properly initialized.");

		NetworkImportingKit::INetworkProcessor* piNetworkProcessor = NULL;
		result resultCode = piImportManager_->CreateEmptyNetwork(&piNetworkProcessor);
		if (FAILED(resultCode) || !piNetworkProcessor)
		{
			Console::EventNotify("Error: Creating empty network project.");
			Console::EventNotify("Descr: Error during CreateEmptyNetwork call.");
			Console::EventNotify("Code: resultCode = result resultCode = piImportManager_->CreateEmptyNetwork(&piNetworkProcessor);");

			throw ConsoleException("Component initialization failed.");
		}		
	
        return piNetworkProcessor;
	}

	result LoadNLProject(const StringA& fileName, NetworkImportingKit::INetworkProcessor** piNetProc)
	{
		return piImportManager_->LoadNLProject(fileName, piNetProc);
	}	

	result StoreNLProject(const StringA& fileName, NetworkImportingKit::INetworkProcessor* piNetProc)
	{
		return piImportManager_->StoreNLProject(fileName, piNetProc);
	}	

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	void CleanUp()
	{
		if (piImportManager_)
			piImportManager_->Release();
		if (piLoader_)
			piLoader_->Release();
		
		piLoader_ = NULL;
		piImportManager_ = NULL;
	}

	// Members
	//////////////////////////////////////////////////////////////////////////
	IComponentLoader*								piLoader_;
	NetworkImportingKit::IImportManager*			piImportManager_;

};

#endif // !NETWORKIMPORTHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
