#ifndef NETWORKIMPORTHELPER_H__WORKSPACE__INCLUDED_
#define NETWORKIMPORTHELPER_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class NetworkImportHelper
{
public:
	NetworkImportHelper()
		: piLoader_(NULL)
		, piImportManager_(NULL)
	{
	}

	result Initialize()
	{
		piLoader_ = CConstructTool<CComponentLoader, IComponentLoader>
			::ConstructObject(IID_IComponentLoader);
		assert(piLoader_ != NULL);

		piLoader_->SetLibraryName(StringA("./NetworkImport") + SO_LIB_EXT);
		result resultCode = piLoader_->InitializeComponentInstance(NetworkImportingKit::CLSID_NetworkImport);
		if (FAILED(resultCode))
		{
			CleanUp();
            return WS_E_IMPORTMNG_LOAD;
		}
		
		resultCode = piLoader_->QueryComponentObject(NetworkImportingKit::IID_IImportManager, (void**)&piImportManager_);
		if (FAILED(resultCode) || !piImportManager_)
		{
			CleanUp();
			return WS_E_IMPORTMNG_INIT;
		}

		if (FAILED(piImportManager_->InitializeManager()))
		{
			CleanUp();
			return WS_E_IMPORTMNG_INIT;
		}

		return S_OK;			 
	}

	void Free()
	{
		CleanUp();
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
			return NULL;

		NetworkImportingKit::INetworkProcessor* piNetworkProcessor = NULL;
		result resultCode = piImportManager_->CreateEmptyNetwork(&piNetworkProcessor);
		if (FAILED(resultCode))
			return NULL;

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

}

#endif // !NETWORKIMPORTHELPER_H__WORKSPACE__INCLUDED_
