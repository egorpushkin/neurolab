//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StorageProcessor.h
//	Description: The CStorageProcessor declaration.  

#ifndef CLASS_STORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_
#define CLASS_STORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_

#include "../StorageProcessor.h"

// CStorageProcessor declaration
class CStorageProcessor 
	: public StorageProcessorKit::IStorageProcessor
{
public:
	CStorageProcessor();
	virtual ~CStorageProcessor();

	// IStorageProcessor declarations section
	virtual result			QueryExternalSerializer(REFCLSID clsid, 
		StorageProcessorCommonKit::IExternalSerializer** ppiSerializer);
	virtual result			QueryConfigProcessor(REFCLSID clsid, 
		StorageProcessorCommonKit::IConfig** ppiConfig);

	// ICommon declarations section	
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	ulong					numRef_;
};

#endif // !CLASS_STORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_
