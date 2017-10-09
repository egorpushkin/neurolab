//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ICHF.cpp
//	Description: Implementation of external helpers.  

#include "../../Headers/CmnComponentsLib.h"

using namespace ComponentsKit;

// CreateKitInstance implementation
result CreateKitInstance(
	REFCLSID		clsid,
	ICommon*		piCommon,
	dword			/* clsContext */,
	REFIID			iid,
	void**			ppObject)
{
	if (clsid != CLSID_ComponentsKit)
		return REGDB_E_CLASSNOTREG;

	if (piCommon != NULL)
		return CLASS_E_NOAGGREGATION;

	// Enumerating registred 'Components Kit' interfaces 
	// Internal Registration Database is being represented as a chain of verifications
	if (iid == IID_IComponentLoader)
	{
		*ppObject = CConstructTool<CComponentLoader, IComponentLoader>::
			ConstructObject(IID_IComponentLoader);
	} else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	return S_OK;
}

