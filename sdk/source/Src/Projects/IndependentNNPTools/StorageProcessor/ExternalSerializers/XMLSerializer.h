//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: XMLSerializer.h
//	Description: The CXMLSerializer declaration.  

#ifndef XMLSERIALIZER_H__STORAGEPROCESSOR__INCLUDED_
#define XMLSERIALIZER_H__STORAGEPROCESSOR__INCLUDED_

#include "../StorageProcessor.h"

// CXMLSerializer declaration
class CXMLSerializer 
	: public StorageProcessorCommonKit::IExternalSerializer
{
public:
	CXMLSerializer();
	virtual ~CXMLSerializer();

	// IExternalSerializer declarations section
	virtual result			SerializeNLProject(const StringA& fileName, 
		NetworkImportingKit::INetworkProcessor* piNetProc, bool loading);

	virtual void			SetFlags(dword flags);

	// ICommon declarations section	
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	ulong					numRef_;

	dword					flags_;
};

#endif // !XMLSERIALIZER_H__STORAGEPROCESSOR__INCLUDED_
