//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CoreEntries.h
//	Description: Component externals implementation.  

#include "CoreEntries.h"

#include "CommonFactory.h"

using namespace StorageProcessorCommonKit;

ulong lockCount = 0;
ulong objCount = 0;

result DllGetClassObject(REFCLSID rCLSID, REFIID rIID, void** ppObject)
{
	if (rCLSID != CLSID_StorageProcessor)
		return CLASS_E_CLASSNOTAVAILABLE;

	// We only know how to make CObjectsFactory objects in this house.
	if(rIID != IID_ICommonFactory)
		return CLASS_E_CLASSNOTAVAILABLE;

	// They want a CObjectFactory.
	CCommonFactory* pCommonFactory = new CCommonFactory;

	// Go get the interface from the CObjectsFactory. 
	result resultCode = pCommonFactory->QueryInterface(rIID, ppObject);

	if(FAILED(resultCode) || !(*ppObject)) 
		delete pCommonFactory;

	return resultCode; // S_OK or E_NOINTERFACE.
}

result CanUnloadNow()
{
	if(lockCount != 0 || objCount != 0)
		return S_FALSE;

	return S_OK;
}

void GetComponentName(String& componentName)
{
	componentName = _T("StorageProcessor");
}

void GetComponentVersion(String& componentVersion)
{
	componentVersion = _T("1.0.0.1");
}
