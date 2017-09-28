//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CoreEntries.h
//	Description: Component externals declaration.  

#ifndef COREENTRIES_H__BUILDERELEMENTS__INCLUDED_
#define COREENTRIES_H__BUILDERELEMENTS__INCLUDED_

#include "../BuilderElements.h"

BUILDERELEMENTS_FUNC_DECLARE result			DllGetClassObject(REFCLSID rCLSID, REFIID rIID, void** ppObject);
BUILDERELEMENTS_FUNC_DECLARE result			CanUnloadNow();

BUILDERELEMENTS_FUNC_DECLARE void			GetComponentName(String& rComponentName);
BUILDERELEMENTS_FUNC_DECLARE void			GetComponentVersion(String& rComponentVersion);

#endif // !COREENTRIES_H__BUILDERELEMENTS__INCLUDED_
