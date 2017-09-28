//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ComponentLoader.cpp
//	Description: The CComponentLoader implementation file.

#include "../Headers/CmnComponentsLib.h"

using namespace ComponentsKit;

CComponentLoader::CComponentLoader()
	: libraryName_("")
	, pLibrary_(NULL)
	, pDllGetClassObject_(NULL)
	, pCanUnloadNow_(NULL)
	, pGetComponentName_(NULL)
	, pGetComponentVersion_(NULL)
	, pComponentCommonFactory_(NULL)
	, numRef_(0)
{
}

CComponentLoader::CComponentLoader(const StringA& rLibraryName)
	: libraryName_(rLibraryName)
	, pLibrary_(NULL)
	, pDllGetClassObject_(NULL)
	, pCanUnloadNow_(NULL)
	, pGetComponentName_(NULL)
	, pGetComponentVersion_(NULL)
	, pComponentCommonFactory_(NULL)
	, numRef_(0)
{
}

CComponentLoader::~CComponentLoader()
{
	ReleaseComponentInstance();
}

// IComponentLoader implementations section
void CComponentLoader::SetLibraryName(const StringA& rLibraryName)
{
	libraryName_ = rLibraryName;
}

StringA CComponentLoader::GetLibraryName()
{
	return libraryName_;
}

result CComponentLoader::VerifyWhetherExists()
{
	return E_NOTIMPL;
}

result CComponentLoader::InitializeComponentInstance(REFCLSID rCLSID)
{
	if (libraryName_ == "")
		return E_INVALIDARG;

	// Loading component library
	pLibrary_ = SD_LoadLibrary(libraryName_.c_str());
	if (!pLibrary_)
		return STG_E_FILENOTFOUND;

	pDllGetClassObject_	= (PDLL_GET_CLASS_OBJECT_ROUTINE) SD_GetProcAddress(pLibrary_, "DllGetClassObject");
	pCanUnloadNow_			= (PDLL_CAN_UNLOAD_NOW_ROUTINE) SD_GetProcAddress(pLibrary_, "CanUnloadNow");
	pGetComponentName_		= (PGET_COMPONENT_NAME_ROUTINE) SD_GetProcAddress(pLibrary_, "GetComponentName");
	pGetComponentVersion_	= (PGET_COMPONENT_VERSION_ROUTINE) SD_GetProcAddress(pLibrary_, "GetComponentVersion");

	if (!pDllGetClassObject_ ||
		!pCanUnloadNow_ ||
		!pGetComponentName_ ||
		!pGetComponentVersion_)
	{
		SD_FreeLibrary(pLibrary_);
		pLibrary_ = NULL;

		return COMP_E_INVALIDCOMPONENT;
	}

	// Receiving Class Factory object control interface for loaded omponent
	result resCode = (*pDllGetClassObject_)(
		rCLSID, 
		IID_ICommonFactory, 
		(void**)&pComponentCommonFactory_);
	
	if (FAILED(resCode) || !pComponentCommonFactory_)
	{
		SD_FreeLibrary(pLibrary_);
		pLibrary_ = NULL;

		return COMP_E_INVALIDCOMPONENT;
	}

	return S_OK;
}

result CComponentLoader::ReleaseComponentInstance()
{
	if (!IsLoaded())
		return S_FALSE;

	if (!(*pCanUnloadNow_)())
		return S_FALSE;

	pComponentCommonFactory_->Release();

	SD_FreeLibrary(pLibrary_);

	pLibrary_ = NULL;

	return S_OK;
}

bool CComponentLoader::IsLoaded()
{
	return (pLibrary_ != NULL);
}

result CComponentLoader::QueryComponentObject(REFIID rIID, void** ppObject)
{
	if (!IsLoaded())
		return COMP_E_NOTLOADED;

	return pComponentCommonFactory_->CreateInstance(NULL, rIID, ppObject);
}

String CComponentLoader::GetComponentName()
{
	if (IsLoaded())
		return _T("");
	
	String sComponentName;
	(*pGetComponentName_)(sComponentName);

	return sComponentName;
}

String CComponentLoader::GetComponentVersion()
{
	if (IsLoaded())
		return _T("");

	String sComponentVersion;
	(*pGetComponentVersion_)(sComponentVersion);

	return sComponentVersion;
}

// ICommon implementations section
ulong CComponentLoader::AddRef()
{
	return ++numRef_;						
}

ulong CComponentLoader::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CComponentLoader::GetClassString() const
{
	return _T("CComponentLoader");
}

result CComponentLoader::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IComponentLoader)
	{
		*ppObject = (IComponentLoader*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((IComponentLoader*)this)->AddRef();
	return S_OK;
}
