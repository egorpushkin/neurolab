//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CommonFactory.cpp
//	Description: The CCommonFactory implementation.  

#include "CommonFactory.h"

#include "../ElementsStructure/GroupsContainer.h"
#include "../Functions/FunctionsFactory.h"

using namespace BuilderElementsCommonKit;

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

	result resultCode = E_NOINTERFACE;

	if (rIID == IID_IGroupsContainer)
	{
		CGroupsContainer* pGroupsContainer = new CGroupsContainer;

		resultCode = pGroupsContainer->QueryInterface(rIID, ppObject);
		
		if (FAILED(resultCode) || !(*ppObject))
			delete pGroupsContainer;

	} else if (rIID == IID_IFunctionsFactory)
	{
		CFunctionsFactory* pFunctionsFactory = new CFunctionsFactory;

		resultCode = pFunctionsFactory->QueryInterface(rIID, ppObject);

		if (FAILED(resultCode) || !(*ppObject))
			delete pFunctionsFactory;
	}
	
	if (FAILED(resultCode))
	{
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
