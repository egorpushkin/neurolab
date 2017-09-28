//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StoreElement.cpp
//	Description: The CStoreElement implementation.  

#include "LoadElement.h"

#include "../Tools/PrepareDataFileName.h"
#include "../Tools/SerializeDataFactory.h"
#include "../Tools/SerializeLayer.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;
using namespace ExternalOutputEngine;
using namespace StorageProcessorCommonKit;

StringA CLoadElement::projectName_ = "";
StringA CLoadElement::projectFilePath_ = "";
dword CLoadElement::flags_ = 0;

void CLoadElement::SetProjectName(const StringA& projectName)
{
	projectName_ = projectName;
}

void CLoadElement::SetProjectFilePath(const StringA& projectFilePath)
{
	projectFilePath_ = projectFilePath;
}

void CLoadElement::SetFlags(dword flags)
{
	flags_ = flags;
}

result CLoadElement::Load(xmlNodePtr pElementNode, INetworkProcessor* piNetProc)
{
	xmlNodePtr pSectionsNode = pElementNode->xmlChildrenNode;
	if (!pSectionsNode || xmlStrcmp(pSectionsNode->name, (const xmlChar*)"Sections"))
		return SP_XML_E_WRONGFORMAT;

	map<StringA, xmlNodePtr> sectionsHash;
	typedef pair<StringA, xmlNodePtr> SectionPair;
	typedef map<StringA, xmlNodePtr>::iterator SectionIterator;
	
	xmlNodePtr pSectionNode = pSectionsNode->xmlChildrenNode;
	while (pSectionNode)
	{
		sectionsHash.insert(SectionPair(StringA((char*)pSectionNode->name), pSectionNode));
		pSectionNode = pSectionNode->next;
	}	

	IElement* piElement = NULL;

	// CmnElement
	//////////////////////////////////////////////////////////////////////////	
	SectionIterator sectionPos = sectionsHash.find(StringA("CmnElement"));
	if (sectionPos == sectionsHash.end())
		return SP_XML_E_WRONGFORMAT;
    
	result resultCode = ParseCmnElementSection(sectionPos->second, piNetProc, &piElement);
	if (FAILED(resultCode) || !piElement) return resultCode;

	// CmnBuilderElement
	//////////////////////////////////////////////////////////////////////////	
	sectionPos = sectionsHash.find(StringA("CmnBuilderElement"));
	if (sectionPos == sectionsHash.end())
	{
		piElement->Release();
		return SP_XML_E_WRONGFORMAT;	
	}
	
	resultCode = ParseCmnBuilderElementSection(sectionPos->second, piElement);
	if (FAILED(resultCode)) 
	{
		piElement->Release();
		return resultCode;	
	}

	// CmnDataFlow
	//////////////////////////////////////////////////////////////////////////	
	sectionPos = sectionsHash.find(StringA("CmnDataFlow"));
	if (sectionPos == sectionsHash.end())
	{
		piElement->Release();
		return SP_XML_E_WRONGFORMAT;	
	}

	resultCode = ParseCmnDataFlowElementSection(sectionPos->second, piNetProc, piElement);
	if (FAILED(resultCode)) 
	{
		piElement->Release();
		return resultCode;	
	}

	// CmnDataConnector
	//////////////////////////////////////////////////////////////////////////	
	sectionPos = sectionsHash.find(StringA("CmnDataConnector"));
	if (sectionPos == sectionsHash.end())
	{
		piElement->Release();
		return SP_XML_E_WRONGFORMAT;	
	}

	resultCode = ParseCmnConnectionsFactory(sectionPos->second, piNetProc, piElement);
	if (FAILED(resultCode)) 
	{
		piElement->Release();
		return resultCode;	
	}

	// CmnLayer
	//////////////////////////////////////////////////////////////////////////	
	sectionPos = sectionsHash.find(StringA("CmnLayer"));
	if (sectionPos != sectionsHash.end())
	{
		resultCode = ParseCmnLayerElementSection(sectionPos->second, piElement);
		if (FAILED(resultCode)) 
		{
			piElement->Release();
			return resultCode;	
		}
	}

	piElement->Release();

	return S_OK;
}

// CnmElement section
//////////////////////////////////////////////////////////////////////////
result CLoadElement::ParseCmnElementSection(xmlNodePtr pSectionNode, INetworkProcessor* piNetProc, IElement** piElement)
{
	xmlChar* xmlElementName = xmlGetProp(pSectionNode, (const xmlChar *)"name");
	xmlChar* xmlElementId = xmlGetProp(pSectionNode, (const xmlChar *)"id");

	if (!xmlElementName || !xmlElementName)
		return SP_XML_E_WRONGFORMAT;
    
	StringA elementName((char*)xmlElementName);
	uint elementId = atoi((const char*)xmlElementId);

	//xmlFree(xmlElementName);
	//xmlFree(xmlElementId);

	IStructureBuilder* piStructureBuilder = NULL;
	result resultCode = piNetProc->QueryInterface(IID_IStructureBuilder, (void**)&piStructureBuilder);
	if (FAILED(resultCode) || !piStructureBuilder)
		return SP_E_QUERYBUILDER;
	
	(*piElement) = piStructureBuilder->AddElement(elementName);
	if (!(*piElement))
	{
		piStructureBuilder->Release();
		return SP_XML_E_WRONGELEMENTNAME;
	}

	(*piElement)->SetElementID(elementId);

	piStructureBuilder->Release();

	return S_OK;
}

// CmnBuilderElement
//////////////////////////////////////////////////////////////////////////
result CLoadElement::ParseCmnBuilderElementSection(xmlNodePtr pSectionNode, IElement* piElement)
{
	xmlChar* xmlPositionX = xmlGetProp(pSectionNode, (const xmlChar *)"positionx");
	xmlChar* xmlPositionY = xmlGetProp(pSectionNode, (const xmlChar *)"positiony");

	if (!xmlPositionX || !xmlPositionY)
		return SP_XML_E_WRONGFORMAT;

	BuilderPoint point;
	point.x = atoi((const char*)xmlPositionX);
	point.y = atoi((const char*)xmlPositionY);	

	//xmlFree(xmlPositionX);
	//xmlFree(xmlPositionY);

	IBuilderElement* piBuilderElement = NULL;
	result resultCode = piElement->QueryInterface(IID_IBuilderElement, (void**)&piBuilderElement);
	if (FAILED(resultCode) || !piBuilderElement)
		return SP_E_WRONGELEMENTOBJECT;

	piBuilderElement->SetElementPosition(point);

	piBuilderElement->Release();

	return S_OK;
}

// CmnDataFlowElement
//////////////////////////////////////////////////////////////////////////
result CLoadElement::ParseCmnDataFlowElementSection(xmlNodePtr pSectionNode, INetworkProcessor* piNetProc, IElement* piElement)
{
	xmlChar* xmlFunction = xmlGetProp(pSectionNode, (const xmlChar *)"func");
	xmlChar* xmlElementDataFile = xmlGetProp(pSectionNode, (const xmlChar *)"elementdatafile");

	if (!xmlFunction || !xmlElementDataFile)
		return SP_XML_E_WRONGFORMAT;
	
	const StringA functionName((const char*)xmlFunction);
	const StringA elementDataFile((const char*)xmlElementDataFile);	

	//xmlFree(xmlFunction);
	//xmlFree(xmlElementDataFile);

	// Configuring element with transfer function
	IStructureBuilder* piStructureBuilder = NULL;
	result resultCode = piNetProc->QueryInterface(IID_IStructureBuilder, (void**)&piStructureBuilder);
	if (FAILED(resultCode) || !piStructureBuilder)
		return SP_E_QUERYBUILDER;

	resultCode = piStructureBuilder->ApplyTransferFunction(piElement, functionName);
	if (FAILED(resultCode))
	{
		piStructureBuilder->Release();	
		return SP_XML_E_WRONGFORMAT;
	}

	piStructureBuilder->Release();	

	// Reading element data
	StringA elementDataFilePath = 
		projectFilePath_ + 
		elementDataFile;

	IDataFactory* piDataFactory = CSerializeDataFactory::LoadDataFactoryFromFile(elementDataFilePath);
	if (piDataFactory)
	{
		IDataFlow* piDataFlow = NULL;
		resultCode = piElement->QueryInterface(IID_IDataFlow, (void**)&piDataFlow);
		if (FAILED(resultCode) || !piDataFlow)
		{
			piDataFactory->Release();
			return SP_E_QUERYBUILDER;
		}
		
		piDataFlow->SetElementData(piDataFactory);
		
		piDataFlow->Release();
		piDataFactory->Release();
	}

	return S_OK;
}


// CmnDataConnector
//////////////////////////////////////////////////////////////////////////
result CLoadElement::ParseCmnConnectionsFactory(xmlNodePtr pSectionNode, INetworkProcessor* piNetProc, IElement* piElement)
{
//	pSectionNode = pSectionNode->xmlChildrenNode;
	if (!pSectionNode)
        return SP_XML_E_WRONGFORMAT;

	IStructureBuilder* piStructureBuilder = NULL;
	result resultCode = piNetProc->QueryInterface(IID_IStructureBuilder, (void**)&piStructureBuilder);
	if (FAILED(resultCode) || !piStructureBuilder)
		return SP_E_QUERYBUILDER;

	xmlNodePtr pFactoryNode = pSectionNode->xmlChildrenNode;
	while (pFactoryNode)
	{
		if (!xmlStrcmp(pFactoryNode->name, (const xmlChar *)"ConnectionsFactory"))
		{		
			result resultCode = ParseProcessFactoryNode(pFactoryNode, piStructureBuilder, piElement);
			if (FAILED(resultCode))
			{
				piStructureBuilder->Release();
				return resultCode;
			}
		}

		pFactoryNode = pFactoryNode->next;
	}

	piStructureBuilder->Release();	
    
	return S_OK;
}

result CLoadElement::ParseProcessFactoryNode(xmlNodePtr pFactoryNode, IStructureBuilder* piBuilder, IElement* piElement)
{
	xmlChar* xmlName = xmlGetProp(pFactoryNode, (const xmlChar *)"name");
	if (!xmlName)
		return S_FALSE;

	uint factoryType = DC_NO_FACTORY;
	if (!xmlStrcmp(xmlName, (const xmlChar *)"InputsFactory"))
		factoryType = DC_INPUTS_FACTORY;
	else if (!xmlStrcmp(xmlName, (const xmlChar *)"OutputsFactory"))
		factoryType = DC_OUTPUTS_FACTORY;

	//xmlFree(xmlName);	

	if (DC_NO_FACTORY == factoryType)
		return S_FALSE;

	// Enumerating connections
	xmlNodePtr pConnectionNode = pFactoryNode->xmlChildrenNode;
	while (pConnectionNode)
	{
		if (!xmlStrcmp(pConnectionNode->name, (const xmlChar *)"Connection"))
		{		
			result resultCode = ParseProcessConnectionNode(pConnectionNode, factoryType, piBuilder, piElement);
			if (FAILED(resultCode))
				return resultCode;
		}

		pConnectionNode = pConnectionNode->next;
	}

	return S_OK;
}

result CLoadElement::ParseProcessConnectionNode(xmlNodePtr pConnectionNode, uint factoryType, IStructureBuilder* piBuilder, IElement* piElement)
{
	xmlChar* xmlThis = xmlGetProp(pConnectionNode, (const xmlChar *)"this");
	xmlChar* xmlOpposite = xmlGetProp(pConnectionNode, (const xmlChar *)"opposite");
	xmlChar* xmlHasData = xmlGetProp(pConnectionNode, (const xmlChar *)"hasdata");
	xmlChar* xmlSize = xmlGetProp(pConnectionNode, (const xmlChar *)"size");
	xmlChar* xmlWeightsDatafile = xmlGetProp(pConnectionNode, (const xmlChar *)"weightsdatafile");
	xmlChar* xmlDatafile = xmlGetProp(pConnectionNode, (const xmlChar *)"datafile");

	if (!xmlThis || !xmlOpposite || !xmlHasData || !xmlSize || !xmlWeightsDatafile || !xmlDatafile)
		return SP_XML_E_WRONGFORMAT;

	// Create and initialize connection
	uint connectionSize = atoi((const char*)xmlSize);

	CConnection* pConnecton = piBuilder->CreateConnection(connectionSize);
	if (!pConnecton)
		return SP_E_BUILDERALLOCATEERROR;

	pConnecton->prevPtr_ = atoi((const char*)xmlThis);
	pConnecton->prevOpositePtr_ = atoi((const char*)xmlOpposite);

	pConnecton->hasData_ = false;
	if (!xmlStrcmp(xmlHasData, (const xmlChar *)"true"))
		pConnecton->hasData_ = true;

	StringA weightsDataFilePsth = 
		projectFilePath_ + 
		StringA((char*)xmlWeightsDatafile);

	StringA dataFilePsth = 
		projectFilePath_ + 
		StringA((char*)xmlDatafile);

	//xmlFree(xmlThis);
	//xmlFree(xmlOpposite);
	//xmlFree(xmlHasData);
	//xmlFree(xmlSize);
	//xmlFree(xmlWeightsDatafile);
	//xmlFree(xmlDatafile);	

	IDataFactory* piWeightsData = CSerializeDataFactory::LoadDataFactoryFromFile(weightsDataFilePsth);
	if (piWeightsData)
	{
		if (piWeightsData->GetDataLength() != connectionSize)
		{
			pConnecton->Release();
            return SP_XML_E_WRONGEXTERNALDATA;
		}

		pConnecton->weights_.SetData(piWeightsData);
        
		piWeightsData->Release();
	}

	IDataFactory* piData = CSerializeDataFactory::LoadDataFactoryFromFile(dataFilePsth);
	if (piData)
	{
		if (piData->GetDataLength() != connectionSize)
		{
			pConnecton->Release();
			return SP_XML_E_WRONGEXTERNALDATA;
		}

		pConnecton->data_.SetData(piData);

		piData->Release();
	}

	// Add connection to the corresponding factory
	IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::QueryInterface(piElement, IID_IDataConnector);

	IConnectionsFactory* piFactory = piDataConnector->GetConnectionsFactory(factoryType);
	piFactory->AddConnection(pConnecton, true);
	piFactory->Release();

	piDataConnector->Release();

	return S_OK;
}

// CnmLayer
//////////////////////////////////////////////////////////////////////////
result CLoadElement::ParseCmnLayerElementSection(xmlNodePtr pSectionNode, IElement* piElement)
{
	xmlChar* xmlInputsCount = xmlGetProp(pSectionNode, (const xmlChar *)"inputscount");
	xmlChar* xmlDimension = xmlGetProp(pSectionNode, (const xmlChar *)"dimension");
	xmlChar* xmlWeightsfile = xmlGetProp(pSectionNode, (const xmlChar *)"weightsfile");
	xmlChar* xmlDeltasfile = xmlGetProp(pSectionNode, (const xmlChar *)"deltasfile");
	
	if (!xmlInputsCount || !xmlDimension || !xmlWeightsfile || !xmlDeltasfile)
		return SP_XML_E_WRONGFORMAT;

	uint inputsCount = atoi((const char*)xmlInputsCount);
	uint dimension = atoi((const char*)xmlDimension);    

	StringA weightsFilePsth = 
		projectFilePath_ + 
		StringA((char*)xmlWeightsfile);

	StringA deltasFilePsth = 
		projectFilePath_ + 
		StringA((char*)xmlDeltasfile);

	//xmlFree(xmlInputsCount);	
	//xmlFree(xmlDimension);	
	//xmlFree(xmlWeightsfile);	
	//xmlFree(xmlDeltasfile);	

	ILayerControl* piLayerControl = NULL;
	result resultCode = piElement->QueryInterface(IID_ILayerControl, (void**)&piLayerControl);
	if (FAILED(resultCode) || !piLayerControl)
		return S_FALSE;

	piLayerControl->CreateWeights(inputsCount, dimension);

	CSerializeLayer::SerializeWeights(weightsFilePsth, piLayerControl, ModeLoad);
	CSerializeLayer::SerializeDeltas(deltasFilePsth, piLayerControl, ModeLoad);

	piLayerControl->Release();

	return S_OK;
}
