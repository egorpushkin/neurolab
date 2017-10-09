//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StoreElement.cpp
//	Description: The CStoreElement implementation.  

#include "StoreElement.h"

#include "../Tools/PrepareDataFileName.h"
#include "../Tools/SerializeDataFactory.h"
#include "../Tools/SerializeLayer.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;
using namespace ExternalOutputEngine;
using namespace StorageProcessorCommonKit;

StringA CStoreElement::projectName_ = "";
StringA CStoreElement::projectFilePath_ = "";
dword CStoreElement::flags_ = 0;

void CStoreElement::SetProjectName(const StringA& projectName)
{
	projectName_ = projectName;
}

void CStoreElement::SetProjectFilePath(const StringA& projectFilePath)
{
	projectFilePath_ = projectFilePath;
}

void CStoreElement::SetFlags(dword flags)
{
	flags_ = flags;
}

result CStoreElement::Store(xmlTextWriterPtr pWriter, IElement* piElement)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "Element");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "Sections");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	// Writing element sections
	result resultCode = StoreCmnElementSection(pWriter, piElement);
	if (FAILED(resultCode)) return resultCode;

	resultCode = StoreCmnBuilderElementSection(pWriter, piElement);
	if (FAILED(resultCode)) return resultCode;

	resultCode = StoreCmnDataFlowSection(pWriter, piElement);
	if (FAILED(resultCode)) return resultCode;

	resultCode = StoreCmnDataConnectorSection(pWriter, piElement);
	if (FAILED(resultCode)) return resultCode;

	resultCode = StoreCmnLayerSection(pWriter, piElement);
	if (FAILED(resultCode)) return resultCode;

	// Close the element named <Sections>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	// Close the element named <Element>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}

// CnmElement section
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreCmnElementSection(xmlTextWriterPtr pWriter, IElement* piElement)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "CmnElement");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	// Add an attribute with name "name" <CmnElement>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "name", BAD_CAST piElement->GetSysName().c_str());
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Add an attribute with name "title" to <CmnElement>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "title", BAD_CAST piElement->GetSysTitle().c_str());
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Add an attribute with name "id" to <CmnElement>.
	char tmId[10];
	sprintf(tmId, "%d", piElement->GetElementID());

	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "id", BAD_CAST tmId);
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Close the element named <CmnElement>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}

// CmnBuilderElement section
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreCmnBuilderElementSection(xmlTextWriterPtr pWriter, IElement* piElement)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "CmnBuilderElement");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	IBuilderElement* piBuilderElement = QueryTool<IElement, IBuilderElement>::
		QueryInterface(piElement, IID_IBuilderElement);

	BuilderPoint tmPoint = piBuilderElement->GetElementPosition();

	piBuilderElement->Release();

	char tmPosition[10];

	// Add an attribute with name "position_x" to <CmnBuilderElement>.
	sprintf(tmPosition, "%d", tmPoint.x);
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "positionx", BAD_CAST tmPosition);
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Add an attribute with name "position_y" to <CmnBuilderElement>.
	sprintf(tmPosition, "%d", tmPoint.y);
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "positiony", BAD_CAST tmPosition);
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Close the element named <CmnBuilderElement>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;
		
	return S_OK;
}

// CnmDataFlow section
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreCmnDataFlowSection(xmlTextWriterPtr pWriter, IElement* piElement)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "CmnDataFlow");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
		QueryInterface(piElement, IID_IDataFlow);

	StringA functionName = piDataFlow->GetFunctionName();

	// Add an attribute with name "func" to <CnmDataFlow>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "func", BAD_CAST functionName.c_str());
	if (xmlResultCode < 0) 
	{
		piDataFlow->Release();
		return  SP_XML_E_ADDATTRIBUTE;
	}

	StringA elementDataFileName = PrepareDataFileName(
		projectName_, 
		piElement->GetSysName(), 
		piElement->GetElementID(), 
		FILE_SUFFIX_ELEMENT_DATA);

	// Add an attribute with name "elementDataFile" to <CnmDataFlow>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "elementdatafile", BAD_CAST elementDataFileName.c_str());
	if (xmlResultCode < 0) 
	{
		piDataFlow->Release();
		return  SP_XML_E_ADDATTRIBUTE;
	}

	// Serializing element data
	StringA filePath = 
		projectFilePath_ + 
		elementDataFileName;

	IDataFactory* piElementData = piDataFlow->GetDataFactory();

    bool saveData = false;
	if (
		((piElement->GetElementType() == ET_INPUT) && (FlagsProcessor::IsSet(flags_, FLAG_ET_INPUT_OFFSET, FLAG_STORE_DATA))) || 
		((piElement->GetElementType() == ET_OUTPUT) && (FlagsProcessor::IsSet(flags_, FLAG_ET_OUTPUT_OFFSET, FLAG_STORE_DATA))) || 
		((piElement->GetElementType() == ET_PROCESSOR) && (FlagsProcessor::IsSet(flags_, FLAG_ET_PROCESSOR_OFFSET, FLAG_STORE_DATA)))
	)
		saveData = true;

	if (saveData)
	{
		result resultCode = CSerializeDataFactory::Serialize(filePath, piElementData, ModeStore);
		if (FAILED(resultCode))
		{
			piElementData->Release();
			piDataFlow->Release();

			return resultCode;
		}
	}

	piElementData->Release();
	piDataFlow->Release();

	// Close the element named <CnmDataFlow>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}

// CnmDataConnector section
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreCmnDataConnectorSection(xmlTextWriterPtr pWriter, IElement* piElement)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "CmnDataConnector");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
		QueryInterface(piElement, IID_IDataConnector);

	result resultCode = StoreConnectionsFactory(pWriter, piDataConnector, DC_INPUTS_FACTORY, "InputsFactory");
	if (FAILED(resultCode)) 
	{
		piDataConnector->Release();
		return resultCode;
	}
	
	resultCode = StoreConnectionsFactory(pWriter, piDataConnector, DC_OUTPUTS_FACTORY, "OutputsFactory");
	if (FAILED(resultCode)) 
	{
		piDataConnector->Release();
		return resultCode;
	}

	piDataConnector->Release();

	// Close the element named <CnmDataConnector>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}

// CnmDataConnector::ConnectionsFactory block
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreConnectionsFactory(xmlTextWriterPtr pWriter, IDataConnector* piDataConnector, uint factoryType, const StringA& factoryName)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "ConnectionsFactory");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	// Add an attribute with name "name" to <ConnectionsFactory>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "name", BAD_CAST factoryName.c_str());
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Enumerating and serializing connections
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(factoryType);
	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();

	for (bool hasConnections = piConnectionsEnum->SelectFirst();hasConnections;hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		StoreConnection(pWriter, factoryType, pConnection);
	}

	piConnectionsEnum->Release();
	piConnectionsFactory->Release();

	// Close the element named <ConnectionsFactory>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}

// CnmDataConnector::ConnectionsFactory::Connection block
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreConnection(xmlTextWriterPtr pWriter, uint factoryType, CConnection* pConnection)
{
	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "Connection");
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDELEMENT;

	char tmPointer[11];
	sprintf(tmPointer, "%ld", pConnection);

	// Add an attribute with name "this" to <Connection>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "this", BAD_CAST tmPointer);
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	sprintf(tmPointer, "%ld", pConnection->pOpposite_);

	// Add an attribute with name "opposite" to <Connection>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "opposite", BAD_CAST tmPointer);
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	StringA strHasData("true");
	if (!pConnection->hasData_)
		strHasData = "false";

	// Add an attribute with name "has_data" to <Connection>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "hasdata", BAD_CAST strHasData.c_str());
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	StringA weightsDataFileName = PrepareDataFileName(
		projectName_, 
		"Connection", 
		(uint)pConnection, 
		FILE_SUFFIX_CONNECTION_WEIGHTS);

	sprintf(tmPointer, "%d", pConnection->data_.GetDataLength());

	// Add an attribute with name "size" to <Connection>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "size", BAD_CAST tmPointer);
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Add an attribute with name "weightsDataFile" to <Connection>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "weightsdatafile", BAD_CAST weightsDataFileName.c_str());
	if (xmlResultCode < 0) 
		return  SP_XML_E_ADDATTRIBUTE;

	// Serializing connection weights
	StringA filePath = 
		projectFilePath_ + 
		weightsDataFileName;

	ILayerControl* piLayerControl = NULL;
	pConnection->pOpposite_->piElement_->QueryInterface(IID_ILayerControl, (void**)&piLayerControl);
	bool storeExternalData = (!piLayerControl) && (factoryType == DC_INPUTS_FACTORY);
	if (piLayerControl)
		piLayerControl->Release();

	if (FlagsProcessor::IsSet(flags_, FLAG_ET_CONNECTION_OFFSET, FLAG_STORE_WEIGHTS) && storeExternalData)
	{
		result resultCode = CSerializeDataFactory::Serialize(filePath, &pConnection->weights_, ModeStore);
		if (FAILED(resultCode)) return resultCode;
	}

	StringA dataFileName = PrepareDataFileName(
		projectName_, 
		"Connection", 
		(uint)pConnection, 
		FILE_SUFFIX_CONNECTION_DATA);

	// Add an attribute with name "dataFile" to <Connection>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "datafile", BAD_CAST dataFileName.c_str());
	if (xmlResultCode < 0) 
		return SP_XML_E_ADDATTRIBUTE;

	// Serializing connection weights
	filePath = 
		projectFilePath_ + 
		dataFileName;

	if (FlagsProcessor::IsSet(flags_, FLAG_ET_CONNECTION_OFFSET, FLAG_STORE_DATA) && storeExternalData)
	{
		result resultCode = CSerializeDataFactory::Serialize(filePath, &pConnection->data_, ModeStore);
		if (FAILED(resultCode)) return resultCode;
	}

	// Close the element named <Connection>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}

// CnmLayer section
//////////////////////////////////////////////////////////////////////////
result CStoreElement::StoreCmnLayerSection(xmlTextWriterPtr pWriter, IElement* piElement)
{
	ILayerControl* piLayer = NULL;
	result resultCode = piElement->QueryInterface(IID_ILayerControl, (void**)&piLayer);
	if (FAILED(resultCode) || !piLayer)
		return S_FALSE;

	int xmlResultCode = xmlTextWriterStartElement(pWriter, BAD_CAST "CmnLayer");
	if (xmlResultCode < 0) 
	{
		piLayer->Release();
		return SP_XML_E_ADDELEMENT;
	}

	char tmPointer[11];
	sprintf(tmPointer, "%d", piLayer->GetInputsCount());

	// Add an attribute with name "inputsCount" to <CmnLayer>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "inputscount", BAD_CAST tmPointer);
	if (xmlResultCode < 0) 
	{
		piLayer->Release();
		return  SP_XML_E_ADDATTRIBUTE;	
	}

	sprintf(tmPointer, "%d", piLayer->GetDimension());

	// Add an attribute with name "dimension" to <CmnLayer>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "dimension", BAD_CAST tmPointer);
	if (xmlResultCode < 0) 
	{
		piLayer->Release();
		return  SP_XML_E_ADDATTRIBUTE;	
	}

	// Preparing file name to store weights and processing the operation if necessary
	StringA layerWeightsFileName = PrepareDataFileName(
		projectName_, 
		piElement->GetSysName(), 
		piElement->GetElementID(), 
		FILE_SUFFIX_LAYER_WEIGHTS);

	StringA weightsFilePath = 
		projectFilePath_ + 
		layerWeightsFileName;

	bool saveWeights = false;
	if (
		((piElement->GetElementType() == ET_INPUT) && (FlagsProcessor::IsSet(flags_, FLAG_ET_INPUT_OFFSET, FLAG_STORE_WEIGHTS))) || 
		((piElement->GetElementType() == ET_OUTPUT) && (FlagsProcessor::IsSet(flags_, FLAG_ET_OUTPUT_OFFSET, FLAG_STORE_WEIGHTS))) || 
		((piElement->GetElementType() == ET_PROCESSOR) && (FlagsProcessor::IsSet(flags_, FLAG_ET_PROCESSOR_OFFSET, FLAG_STORE_WEIGHTS)))
		)
		saveWeights = true;

	if (saveWeights)
	{
		result resultCode = CSerializeLayer::SerializeWeights(weightsFilePath, piLayer, ModeStore);
		if (FAILED(resultCode)) 
		{
			piLayer->Release();
			return resultCode;
		}
	}

	// Add an attribute with name "weightsFile" to <CmnLayer>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "weightsfile", BAD_CAST layerWeightsFileName.c_str());
	if (xmlResultCode < 0) 
	{
		piLayer->Release();
		return SP_XML_E_ADDATTRIBUTE;
	}

	// Preparing file name to store deltas and processing the operation if necessary
	StringA layerDeltasFileName = PrepareDataFileName(
		projectName_, 
		piElement->GetSysName(), 
		piElement->GetElementID(), 
		FILE_SUFFIX_LAYER_DELTAS);

	StringA deltasFilePath = 
		projectFilePath_ + 
		layerDeltasFileName;

	bool saveDeltas = false;
	if (
		((piElement->GetElementType() == ET_INPUT) && (FlagsProcessor::IsSet(flags_, FLAG_ET_INPUT_OFFSET, FLAG_STORE_DELTAS))) || 
		((piElement->GetElementType() == ET_OUTPUT) && (FlagsProcessor::IsSet(flags_, FLAG_ET_OUTPUT_OFFSET, FLAG_STORE_DELTAS))) || 
		((piElement->GetElementType() == ET_PROCESSOR) && (FlagsProcessor::IsSet(flags_, FLAG_ET_PROCESSOR_OFFSET, FLAG_STORE_DELTAS)))
		)
	{
		if ( piElement->GetSysName() == StringA("RBFLayer") )
			saveDeltas = true;
	}

	if (saveDeltas)
	{
		result resultCode = CSerializeLayer::SerializeDeltas(deltasFilePath, piLayer, ModeStore);
		if (FAILED(resultCode)) 
		{
			piLayer->Release();
			return resultCode;
		}
	}

	// Add an attribute with name "deltasFile" to <CmnLayer>.
	xmlResultCode = xmlTextWriterWriteAttribute(pWriter, BAD_CAST "deltasfile", BAD_CAST layerDeltasFileName.c_str());
	if (xmlResultCode < 0) 
	{
		piLayer->Release();
		return SP_XML_E_ADDATTRIBUTE;
	}

	piLayer->Release();

	// Close the element named <CnmLayer>.
	xmlResultCode = xmlTextWriterEndElement(pWriter);
	if (xmlResultCode < 0) 
		return SP_XML_E_ENDELEMENT;

	return S_OK;
}



















