//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StoreElement.h
//	Description: The CStoreElement declaration.  

#ifndef LOADELEMENT_H__STORAGEPROCESSOR__INCLUDED_
#define LOADELEMENT_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

class CLoadElement
{
public:
	static result				Load(
		xmlNodePtr pElementNode, 
		NetworkImportingKit::INetworkProcessor* piNetProc);

	static void					SetProjectName(const StringA& projectName);
	static void					SetProjectFilePath(const StringA& projectFilePath);
	static void					SetFlags(dword flags);

private:
	static result				ParseCmnElementSection(xmlNodePtr pSectionNode, 
		NetworkImportingKit::INetworkProcessor* piNetProc,
		NetworkImportingKit::IElement** piElement);
	static result				ParseCmnBuilderElementSection(xmlNodePtr pSectionNode, 
		NetworkImportingKit::IElement* piElement);
	static result				ParseCmnDataFlowElementSection(xmlNodePtr pSectionNode, 
		NetworkImportingKit::INetworkProcessor* piNetProc,
		NetworkImportingKit::IElement* piElement);
	static result				ParseCmnConnectionsFactory(xmlNodePtr pSectionNode, 
		NetworkImportingKit::INetworkProcessor* piNetProc,
		NetworkImportingKit::IElement* piElement);
	static result				ParseProcessFactoryNode(xmlNodePtr pFactoryNode, 
		NetworkImportingKit::IStructureBuilder* piBuilder,
		NetworkImportingKit::IElement* piElement);
	static result				ParseProcessConnectionNode(xmlNodePtr pConnectionNode, 
		uint factoryType, 
		NetworkImportingKit::IStructureBuilder* piBuilder,
		NetworkImportingKit::IElement* piElement);
	static result				ParseCmnLayerElementSection(xmlNodePtr pSectionNode, 
		NetworkImportingKit::IElement* piElement);

/*	// Internal serialization helpers
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
		NetworkImportingKit::CConnection* pConnection);
	static result				StoreCmnLayerSection(xmlTextWriterPtr pWriter, 
		NetworkImportingKit::IElement* piElement);*/

	// Internal state
	static StringA projectName_;
	static StringA projectFilePath_;
	static dword flags_;

};

#endif // !LOADELEMENT_H__STORAGEPROCESSOR__INCLUDED_
