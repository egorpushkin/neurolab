//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CoreEntries.h
//	Description: Component externals declaration.  

#ifndef COREENTRIES_H__NETWORKIMPORT__INCLUDED_
#define COREENTRIES_H__NETWORKIMPORT__INCLUDED_

#include "../NetworkImport.h"

NETIMPORT_FUNC_DECLARE result			DllGetClassObject(REFCLSID rCLSID, REFIID rIID, void** ppObject);
NETIMPORT_FUNC_DECLARE result			CanUnloadNow();

NETIMPORT_FUNC_DECLARE void				GetComponentName(String& rComponentName);
NETIMPORT_FUNC_DECLARE void				GetComponentVersion(String& rComponentVersion);

#endif // !COREENTRIES_H__NETWORKIMPORT__INCLUDED_
