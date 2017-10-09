//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDocument.h
//	Description: The CSerializeDocument declaration.  

#ifndef SERIALIZEDOCUMENT_H__STORAGEPROCESSOR__INCLUDED_
#define SERIALIZEDOCUMENT_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

class CSerializeDocument
{
public:
	static result			Serialize(const StringA& fileName,
		NetworkImportingKit::INetworkProcessor* piNetProc, dword flags, bool loading);

private:
	// Internal serialization helpers
	static result			StoreElements(xmlTextWriterPtr pWriter,
		NetworkImportingKit::INetworkProcessor* piNetProc);
	static result			LoadElements(xmlNodePtr pRootElement,
		NetworkImportingKit::INetworkProcessor* piNetProc);
};


#endif // !SERIALIZEDOCUMENT_H__STORAGEPROCESSOR__INCLUDED_
