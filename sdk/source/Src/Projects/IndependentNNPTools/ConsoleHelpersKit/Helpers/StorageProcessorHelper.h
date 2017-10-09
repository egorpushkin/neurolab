//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StorageProcessorHelper.h
//	Description: StorageProcessorHelper declaration and implementation.  

#ifndef STORAGEPROCESSORHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
#define STORAGEPROCESSORHELPER_H__CONSOLEHELPERSKIT__INCLUDED_

class StorageProcessorHelper
{
public:
	StorageProcessorHelper()
		: piLoader_(NULL)
		, piStorageProcessor_(NULL)
		, piXMLSerializer_(NULL)
		, piXMLConfig_(NULL)
	{
		piLoader_ = CConstructTool<CComponentLoader, IComponentLoader>
			::ConstructObject(IID_IComponentLoader);
		assert(piLoader_ != NULL);

		piLoader_->SetLibraryName(StringA("./StorageProcessor") + SO_LIB_EXT);
		result resultCode = piLoader_->InitializeComponentInstance(StorageProcessorCommonKit::CLSID_StorageProcessor);
		if (FAILED(resultCode))
		{
			Console::EventNotify("Error: Loading StorageProcessor component.");
			Console::EventNotify(StringA("Descr: Library module <StorageProcessor") + SO_LIB_EXT + StringA("> not found."));
			Console::EventNotify("Code: result resultCode = piLoader_->InitializeComponentInstance(CLSID_StorageProcessor);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

		resultCode = piLoader_->QueryComponentObject(StorageProcessorCommonKit::IID_IStorageProcessor, (void**)&piStorageProcessor_);
		if (FAILED(resultCode) || !piStorageProcessor_)
		{
			Console::EventNotify("Error: Querying IID_IStorageProcessor interface.");
			Console::EventNotify("Code: resultCode = piLoader_->QueryComponentObject(IID_IStorageProcessor, (void**)&piStorageProcessor_);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

		resultCode = piStorageProcessor_->QueryExternalSerializer(StorageProcessorCommonKit::CLSID_XMLSerializer, &piXMLSerializer_);		
		if (FAILED(resultCode) || !piStorageProcessor_)
		{
			Console::EventNotify("Error: Querying CLSID_XMLSerializer constrol interface.");
			Console::EventNotify("Code: resultCode = piStorageProcessor_->QueryExternalSerializer(CLSID_XMLSerializer, &piXMLSerializer_);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

		resultCode = piStorageProcessor_->QueryConfigProcessor(StorageProcessorCommonKit::CLSID_XMLConfig, &piXMLConfig_);		
		if (FAILED(resultCode) || !piStorageProcessor_)
		{
			Console::EventNotify("Error: Querying CLSID_XMLConfig constrol interface.");
			Console::EventNotify("resultCode = piStorageProcessor_->QueryExternalSerializer(StorageProcessorCommonKit::CLSID_XMLConfig, &piXMLConfig_);");

			CleanUp();

			throw ConsoleException("Component initialization failed.");
		}

	}

	virtual ~StorageProcessorHelper()
	{
		CleanUp();
	}

	// Public interface
	//////////////////////////////////////////////////////////////////////////
	result SerializeNLProject(const StringA& fileName, NetworkImportingKit::INetworkProcessor* piNetProc, bool loading)
	{
		return piXMLSerializer_->SerializeNLProject(fileName, piNetProc, loading);
	}

	StorageProcessorCommonKit::IConfig* GetXMLConfig()
	{
		if (!piXMLConfig_)
			throw ConsoleException("StorageProcessorHelper was not properly initialized.");

		piXMLConfig_->AddRef();
		return piXMLConfig_;
	}

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	void CleanUp()
	{
		if (piXMLConfig_)
			piXMLConfig_->Release();
		if (piXMLSerializer_)
			piXMLSerializer_->Release();
		if (piStorageProcessor_)
			piStorageProcessor_->Release();
		if (piLoader_)
			piLoader_->Release();

		piLoader_ = NULL;
		piStorageProcessor_ = NULL;
		piXMLSerializer_ = NULL;
		piXMLConfig_ = NULL;
	}

	// Members
	//////////////////////////////////////////////////////////////////////////
	IComponentLoader*								piLoader_;
	StorageProcessorCommonKit::IStorageProcessor*	piStorageProcessor_;
	StorageProcessorCommonKit::IExternalSerializer* piXMLSerializer_;
	StorageProcessorCommonKit::IConfig*				piXMLConfig_;

};

#endif // !STORAGEPROCESSORHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
