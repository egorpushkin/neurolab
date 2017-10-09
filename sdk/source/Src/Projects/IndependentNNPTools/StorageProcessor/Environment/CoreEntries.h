//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: CoreEntries.h
//	Description: Component externals declaration.  

#ifndef COREENTRIES_H__STORAGEPROCESSOR__INCLUDED_
#define COREENTRIES_H__STORAGEPROCESSOR__INCLUDED_

#include "../StorageProcessor.h"

STORAGEPROCESSOR_FUNC_DECLARE result		DllGetClassObject(REFCLSID rCLSID, REFIID rIID, void** ppObject);
STORAGEPROCESSOR_FUNC_DECLARE result		CanUnloadNow();

STORAGEPROCESSOR_FUNC_DECLARE void			GetComponentName(String& componentName);
STORAGEPROCESSOR_FUNC_DECLARE void			GetComponentVersion(String& componentVersion);

#endif // !COREENTRIES_H__STORAGEPROCESSOR__INCLUDED_
