//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: CommonFactory.h
//	Description: Component objects factory.  

#ifndef COMMONFACTORY_H__STORAGEPROCESSOR__INCLUDED_
#define COMMONFACTORY_H__STORAGEPROCESSOR__INCLUDED_

#include "../StorageProcessor.h"

class CCommonFactory 
	: public CCommonFactoryImpl
{
public:
	CCommonFactory();
	virtual ~CCommonFactory();

	// ICommonFactory declarations section	
	virtual result			LockServer(bool lock);
	virtual result			CreateInstance(ICommon* pObjOuter, REFIID iid, void** ppObject);

	// ICommon declarations section	
	virtual String			GetClassString() const;	
	virtual result			QueryInterface(REFIID rIID, void** ppObject);
};

#endif // !COMMONFACTORY_H__STORAGEPROCESSOR__INCLUDED_
