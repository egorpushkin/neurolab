//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDocument.cpp
//	Description: The CSerializeDocument implementation.  

#include "SerializeDocument.h"

// Include additional tools
#include "StoreElement.h"
#include "LoadElement.h"

#include "../Tools/FileNameTools.h"

using namespace NetworkImportingKit;

result CSerializeDocument::Serialize(const StringA& fileName, INetworkProcessor* piNetProc, dword flags, bool loading)
{
	result resultCode = S_OK;

	if (loading)
	{
		xmlDocPtr pDocument = xmlParseFile(fileName.c_str());
		if (!pDocument) 
			return STG_E_FILENOTFOUND;

		xmlNodePtr pNode = xmlDocGetRootElement(pDocument);
		if (!pNode)
		{			
			xmlFreeDoc(pDocument);
			return SP_XML_E_NOROOT;
		}

		if (xmlStrcmp(pNode->name, (const xmlChar*)"NetworkProject")) 
		{	
			xmlFreeDoc(pDocument);
			return SP_XML_E_WRONGFORMAT;		
		}

		pNode = pNode->xmlChildrenNode;
		if (!pNode || xmlStrcmp(pNode->name, (const xmlChar*)"NetworkElements"))
		{			
			xmlFreeDoc(pDocument);
			return SP_XML_E_WRONGFORMAT;
		}

		// Receiving project name to store external connected entries
		CLoadElement::SetProjectName(GetProjectName(fileName));
		CLoadElement::SetProjectFilePath(GetProjectFilePath(fileName));
		CLoadElement::SetFlags(flags);

        resultCode = LoadElements(pNode, piNetProc);
		if (FAILED(resultCode))
		{
			IStructureBuilder* piStructureBuilder = NULL;
			piNetProc->QueryInterface(IID_IStructureBuilder, (void**)&piStructureBuilder);

			piStructureBuilder->ReleaseContent();

            piStructureBuilder->Release();
		}

		xmlFreeDoc(pDocument);

	} else
	{
		// Creating xmlNewTextWriter
		int xmlResultCode;
		xmlTextWriterPtr pWriter;

		pWriter = xmlNewTextWriterFilename(fileName.c_str(), 0);
		if (pWriter == NULL) 
			return STG_E_FILENOTFOUND;

		// Start the document with the xml default for the version,
		// encoding DEFAULT_STORAGE_ENCODING and the default for the standalone
		// declaration. 
		xmlResultCode = xmlTextWriterStartDocument(
			pWriter, NULL, DEFAULT_STORAGE_ENCODING, NULL);
		if (xmlResultCode < 0) 
			return SP_XML_E_STARTDOC;

		// Start an element named <NetworkProject>. Since thist is the first
		// element, this will be the root element of the document. 
		xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "NetworkProject");
		if (xmlResultCode < 0) 
			return SP_XML_E_ADDELEMENT;

		// Add an attribute with name "version" and value "1.0" to <NetworkProject>.
		xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "version", BAD_CAST "1.0");
		if (xmlResultCode < 0) 
			return  SP_XML_E_ADDATTRIBUTE;

		// Start an element named <NetworkElements> as a child of <NetworkProject>. 
		// Since thist is the first element, this will be the root element 
		// of the document. 
		xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "NetworkElements");
		if (xmlResultCode < 0) 
			return SP_XML_E_ADDELEMENT;

		// Receiving project name to store external connected entries
		CStoreElement::SetProjectName(GetProjectName(fileName));
		CStoreElement::SetProjectFilePath(GetProjectFilePath(fileName));
		CStoreElement::SetFlags(flags);

		// Serialize network elements
		resultCode = StoreElements(pWriter, piNetProc);

		// Here we could close the element named "NetworkProject" using the
		// function xmlTextWriterEndElement, but since we do not want to
		// write any other elements, we simply call xmlTextWriterEndDocument,
		// which will do all the work.
		xmlResultCode = xmlTextWriterEndDocument(pWriter);
		if (xmlResultCode < 0) 
			return SP_XML_E_ENDDOC;

		xmlFreeTextWriter(pWriter);
	}

	return resultCode;
}

// Internal serialization helpers
result CSerializeDocument::StoreElements(xmlTextWriterPtr pWriter, INetworkProcessor* piNetProc)
{
	result resultCode = S_OK;

	IElementsCollection* piElementsCollection = 
		QueryTool<INetworkProcessor, IElementsCollection>::
		QueryInterface(piNetProc, IID_IElementsCollection);

	IElementsEnumerator* piEnumerator = piElementsCollection->GetElementsEnumerator();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		resultCode = CStoreElement::Store(pWriter, piElement);
		if (FAILED(resultCode))
			break;
	}
	piEnumerator->Release();  	

	piElementsCollection->Release();

	return resultCode;
}

result CSerializeDocument::LoadElements(xmlNodePtr pNetElements, INetworkProcessor* piNetProc)
{
	xmlNodePtr pElementNode = pNetElements->xmlChildrenNode;
	while (pElementNode)
	{
		if (!xmlStrcmp(pElementNode->name, (const xmlChar *)"Element")) 			
		{
			result resultCode = CLoadElement::Load(pElementNode, piNetProc);
			if (FAILED(resultCode))
				return resultCode;
		}

		pElementNode = pElementNode->next;
	}		

	IStructureBuilder* piStructureBuilder = NULL;
	result resultCode = piNetProc->QueryInterface(IID_IStructureBuilder, (void**)&piStructureBuilder);
	if (FAILED(resultCode) || !piStructureBuilder)
		return SP_E_QUERYBUILDER;

	piStructureBuilder->EstablishConnections();

	piStructureBuilder->Release();

	return S_OK;
}
