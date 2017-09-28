//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: IStorageProcessor.h
//	Description: The IStorageProcessor declaration.  

#ifndef ISTORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_
#define ISTORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_

// IStorageProcessor declaration
interface IStorageProcessor : public ICommon
{
	virtual result			QueryExternalSerializer(REFCLSID clsid, IExternalSerializer** ppiSerializer) = 0;
	virtual result			QueryConfigProcessor(REFCLSID clsid, IConfig** ppiConfig) = 0;
};

#endif // !ISTORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_
