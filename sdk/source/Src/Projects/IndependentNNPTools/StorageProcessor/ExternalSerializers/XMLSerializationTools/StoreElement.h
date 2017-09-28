//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StoreElement.h
//	Description: The CStoreElement declaration.  

#ifndef STOREELEMENT_H__STORAGEPROCESSOR__INCLUDED_
#define STOREELEMENT_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

class CStoreElement
{
public:
	static result				Store(
		xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);

	static void					SetProjectName(const StringA& projectName);
	static void					SetProjectFilePath(const StringA& projectFilePath);
	static void					SetFlags(dword flags);

private:
	// Internal serialization helpers
	static result				StoreCmnElementSection(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);
	static result				StoreCmnBuilderElementSection(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);
	static result				StoreCmnDataFlowSection(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);
	static result				StoreCmnDataConnectorSection(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);
	static result				StoreConnectionsFactory(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IDataConnector* piDataConnector, 
		uint factoryType, const StringA& factoryName);
	static result				StoreConnection(xmlTextWriterPtr pWriter, 
		uint factoryType, 
		NetworkImportingKit::CConnection* pConnection);
	static result				StoreCmnLayerSection(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);

	// Internal state
	static StringA projectName_;
	static StringA projectFilePath_;
	static dword flags_;

};

#endif // !STOREELEMENT_H__STORAGEPROCESSOR__INCLUDED_
