//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDataFactory.h
//	Description: The CSerializeDataFactory declaration.  

#ifndef SERIALIZEDATAFACTORY_H__STORAGEPROCESSOR__INCLUDED_
#define SERIALIZEDATAFACTORY_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

class CSerializeDataFactory
{
public:
	static result				Serialize(const StringA& fileName, IDataFactory* piDataFactory, bool loading);
	static IDataFactory*		LoadDataFactoryFromFile(const StringA& fileName);

private:
	// Internal serialization helpers
	static result				Store(FILEDev& fileDev, IDataFactory* piDataFactory);
	static result				Load(FILEDev& fileDev, IDataFactory* piDataFactory);
};

#endif // !SERIALIZEDATAFACTORY_H__STORAGEPROCESSOR__INCLUDED_

