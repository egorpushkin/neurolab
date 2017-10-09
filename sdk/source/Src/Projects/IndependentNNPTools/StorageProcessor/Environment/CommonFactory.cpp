//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: CommonFactory.cpp
//	Description: The CCommonFactory implementation.  

#include "CommonFactory.h"

#include "../StorageProcessor/StorageProcessor.h"

using namespace StorageProcessorCommonKit;

extern ulong lockCount;
extern ulong objCount;

CCommonFactory::CCommonFactory()
{
	objCount++;
}

CCommonFactory::~CCommonFactory()
{
	lockCount--;
}

// ICommonFactory implementations section	
result CCommonFactory::LockServer(bool Lock)
{
	if(Lock)
		++lockCount;
	else
		--lockCount;

	return S_OK;
}

result CCommonFactory::CreateInstance(ICommon* pObjOuter, REFIID iid, void** ppObject)
{
	if(pObjOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	CStorageProcessor* pStorageProcessor = new CStorageProcessor;

	result resultCode = pStorageProcessor->QueryInterface(iid, ppObject);
    	
	if (FAILED(resultCode) || !(*ppObject))
	{
		delete pStorageProcessor;

		*ppObject = NULL;
		resultCode = E_NOINTERFACE;
	}

	return resultCode;
}

// ICommon implementations section	
String CCommonFactory::GetClassString() const
{
	return _T("CCommonFactory");
}

result CCommonFactory::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_ICommonFactory)
	{
		*ppObject = (ICommonFactory*)this;			
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
