//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CommonFactory.cpp
//	Description: The CCommonFactory implementation.  

#include "CommonFactory.h"
#include "../ImportManager/ImportManager.h"

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

result CCommonFactory::CreateInstance(ICommon* pObjOuter, REFIID rIID, void** ppObject)
{
	if(pObjOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	CImportManager* pImportManager = new CImportManager;

	// Ask car for an interface.
	result resultCode = pImportManager->QueryInterface(rIID, ppObject);

	// Problem?  We must delete the memory we allocated.
	if (FAILED(resultCode) || !(*ppObject))
		delete pImportManager;

	return resultCode; // S_OK or E_NOINTERFACE.
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
