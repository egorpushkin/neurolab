//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ImportManager.cpp
//	Description: Import Manager component implementation.  

#include "ImportManager.h"

#include "../NeuroFactory/NeuroFactory.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CImportManager::CImportManager()
	: piGroupsContainer_(NULL)
	, piFunctionsFactory_(NULL)
	, piBuilderElementsComponent_(NULL)
	, initialized_(false)
	, numRef_(0)
{
	CComponentLoader* pBulderElementsLoader = new CComponentLoader;
	
	pBulderElementsLoader->QueryInterface(IID_IComponentLoader, (void**)&piBuilderElementsComponent_);

	piBuilderElementsComponent_->SetLibraryName(StringA("./BuilderElements") + SO_LIB_EXT);
}

CImportManager::~CImportManager()
{
	if (piGroupsContainer_)
		piGroupsContainer_->Release();
	if (piFunctionsFactory_)
		piFunctionsFactory_->Release();

	if (piBuilderElementsComponent_)
		piBuilderElementsComponent_->Release();    
}

// IImportManager implementations section	
result CImportManager::InitializeManager()
{
	if (initialized_)
		return COMP_E_ALREADYINITIALIZED;

	result resultCode = piBuilderElementsComponent_->InitializeComponentInstance(CLSID_BuilderElements);
	if (FAILED(resultCode))
		return COMP_E_ERRORDLOADING;

	resultCode = piBuilderElementsComponent_->QueryComponentObject(IID_IGroupsContainer, (void**)&piGroupsContainer_);
	if (FAILED(resultCode) || !piGroupsContainer_)
	{
		piBuilderElementsComponent_->ReleaseComponentInstance();

		return COMP_E_ERRORDLOADING;
	}

	resultCode = piBuilderElementsComponent_->QueryComponentObject(IID_IFunctionsFactory, (void**)&piFunctionsFactory_);
	if (FAILED(resultCode) || !piFunctionsFactory_)
	{
		piBuilderElementsComponent_->ReleaseComponentInstance();
		piGroupsContainer_->Release();

		return COMP_E_ERRORDLOADING;
	}

	// Required post initializations
	piGroupsContainer_->SetFunctionsFactory(piFunctionsFactory_);

	initialized_ = true;

	return S_OK;
}

result CImportManager::LoadNLProject(const StringA& fileName, INetworkProcessor** ppiNetProc)
{
	*ppiNetProc = NULL;

	if (!initialized_)
		return COMP_E_NOTLOADED;

	CNeuroFactory* pNeuroFactory = new CNeuroFactory;

	IStorageController* piStorageController = NULL;    
	pNeuroFactory->QueryInterface(IID_IStorageController, (void**)&piStorageController);

	IFactoryControl* piFactoryControl = NULL;
	pNeuroFactory->QueryInterface(IID_IFactoryControl, (void**)&piFactoryControl);
	piFactoryControl->SetBuilderElementsControls(piGroupsContainer_, piFunctionsFactory_);
	piFactoryControl->Release();

	FILEDev fileDev;
	result resultCode = fileDev.Open(fileName.c_str(), ModeReadBinary);
	if (FAILED(resultCode))
	{
		piStorageController->Release();

		return STG_E_FILENOTFOUND;
	}

	resultCode = piStorageController->Serialize(fileDev, ModeLoad);
	if (FAILED(resultCode))
	{
		piStorageController->Release();

		return STG_E_INVALIDFORMAT;
	}

	fileDev.Close();
	
    resultCode = piStorageController->QueryInterface(IID_INetworkProcessor, (void**)ppiNetProc);
	piStorageController->Release();

	return resultCode;
}

result CImportManager::StoreNLProject(const StringA& fileName, INetworkProcessor* piNetProc)
{
	if (!initialized_)
		return COMP_E_NOTLOADED;

	FILEDev fileDev;
	result resultCode = fileDev.Open(fileName.c_str(), ModeWriteBinary);
	if (FAILED(resultCode))
		return STG_E_FILENOTFOUND;

	IStorageController* piStorageController = 
		QueryTool<INetworkProcessor, IStorageController>::
			QueryInterface(piNetProc, IID_IStorageController);
	
	resultCode = piStorageController->Serialize(fileDev, ModeStore);

	piStorageController->Release();

	fileDev.Close();

	return resultCode;
}

result CImportManager::CreateEmptyNetwork(INetworkProcessor** ppiNetProc)
{
	*ppiNetProc = NULL;

	if (!initialized_)
		return COMP_E_NOTLOADED;

	IFactoryControl* piFactoryControl = 
		CConstructTool<CNeuroFactory, IFactoryControl>::
			ConstructObject(IID_IFactoryControl);
	
	piFactoryControl->SetBuilderElementsControls(piGroupsContainer_, piFunctionsFactory_);

	result resultCode = piFactoryControl->QueryInterface(IID_INetworkProcessor, (void**)ppiNetProc);
	
	piFactoryControl->Release();

	return resultCode;
}

// ICommon implementations section
ulong CImportManager::AddRef()
{
	return ++numRef_;						
}

ulong CImportManager::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CImportManager::GetClassString() const
{
	return _T("CImportManager");
}

result CImportManager::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IImportManager)
	{
		*ppObject = (IImportManager*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
