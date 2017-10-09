//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CommonFactory.h
//	Description: Component objects factory.  

#ifndef COMMONFACTORY_H__BUILDERELEMENTS__INCLUDED_
#define COMMONFACTORY_H__BUILDERELEMENTS__INCLUDED_

#include "../BuilderElements.h"

class CCommonFactory 
	: public CCommonFactoryImpl
{
public:
	CCommonFactory();
	virtual ~CCommonFactory();

	// ICommonFactory declarations section	
	virtual result			LockServer(bool lock);
	virtual result			CreateInstance(ICommon* pObjOuter, REFIID rIID, void** ppObject);

	// ICommon declarations section	
	virtual String			GetClassString() const;	
	virtual result			QueryInterface(REFIID rIID, void** ppObject);
};

#endif // !COMMONFACTORY_H__BUILDERELEMENTS__INCLUDED_
