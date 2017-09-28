//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDocument.cpp
//	Description: The CSerializeDocument implementation.  

#include "../../StorageProcessor.h"

#include "SerializeConfig.h"

result CSerializeConfig::Serialize(const StringA& fileName, SpKit::ILayersContainerRef layersContainer,
	SpKit::IArgumentsContainerRef argumentsContainer, CLSID& trainerId, bool loading)
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

		if (xmlStrcmp(pNode->name, (const xmlChar*)"Config")) 
		{	
			xmlFreeDoc(pDocument);
			return SP_XML_E_WRONGFORMAT;		
		}

		pNode = pNode->xmlChildrenNode;
		while (pNode)
		{
			if (!xmlStrcmp(pNode->name, (const xmlChar*)"NetworkProject"))
			{
				resultCode = ParseProject(pNode, layersContainer);
				if (FAILED(resultCode))
					break;
			} else if (!xmlStrcmp(pNode->name, (const xmlChar*)"Arguments"))
			{
				resultCode = ParseArguments(pNode, argumentsContainer);
				if (FAILED(resultCode))
					break;
			} else if (!xmlStrcmp(pNode->name, (const xmlChar*)"Trainer"))
			{
				resultCode = ParseTrainer(pNode, trainerId);
				if (FAILED(resultCode))
					break;
			}	

			pNode = pNode->next;
		}

		xmlFreeDoc(pDocument);

	} else
		return E_NOTIMPL;

	return resultCode;
}

// Internal serialization helpers
result CSerializeConfig::ParseProject(xmlNodePtr pProjectNode, SpKit::ILayersContainerRef layersContainer)
{
	xmlNodePtr pLayerNode = pProjectNode->xmlChildrenNode;
	while (pLayerNode)
	{
		if ( !xmlStrcmp(pLayerNode->name, (const xmlChar*)"Layer") )
		{
			xmlChar* xmlLayerName = xmlGetProp(pLayerNode, (const xmlChar *)"name");
			xmlChar* xmlFunc = xmlGetProp(pLayerNode, (const xmlChar *)"func");
			xmlChar* xmlNeurons = xmlGetProp(pLayerNode, (const xmlChar *)"neurons");
			xmlChar* xmlBias = xmlGetProp(pLayerNode, (const xmlChar *)"bias");

			if ( xmlLayerName && xmlFunc && xmlNeurons )
			{
				StringA layerName((char*)xmlLayerName);
				StringA func((char*)xmlFunc);
				uint neurons = atoi((char*)xmlNeurons);

				SpKit::LayerDataPtr data(new SpKit::LayerData);

				data->layerName_ = layerName;
				data->transferFunction_ = func;
				data->neurons_ = neurons;

				data->hasBias_ = false;
				if ( xmlBias )
					data->hasBias_ = true;

                layersContainer->Add(data);
			}
		}

		pLayerNode = pLayerNode->next;
	}	
		
	return S_OK;
}

result CSerializeConfig::ParseArguments(xmlNodePtr pArgumentsNode, SpKit::IArgumentsContainerRef argumentsContainer)
{
	xmlNodePtr pArgumentNode = pArgumentsNode->xmlChildrenNode;
	while (pArgumentNode)
	{
		if (!xmlStrcmp(pArgumentNode->name, (const xmlChar*)"Argument"))
		{
			xmlChar* xmlName = xmlGetProp(pArgumentNode, (const xmlChar *)"name");
			xmlChar* xmlValue = xmlGetProp(pArgumentNode, (const xmlChar *)"value");
			xmlChar* xmlType = xmlGetProp(pArgumentNode, (const xmlChar *)"type");

			if (xmlName && xmlValue && xmlType)
			{
				StringA name((char*)xmlName);
				StringA value((char*)xmlValue);
				StringA type((char*)xmlType);

				MinCOM::CommonVariant varArg;

				if ( FAILED(ParseArgument(value, type, varArg)) )
					continue;

				argumentsContainer->Add(SpKit::ArgumentsPair(name, varArg));
			}
		}	

		pArgumentNode = pArgumentNode->next;
	}
	
	return S_OK;
}

result CSerializeConfig::ParseTrainer(xmlNodePtr pTrainerNode, CLSID& trainerId)
{
	xmlChar* xmlClsid = xmlGetProp(pTrainerNode, (const xmlChar *)"clsid");

	if (xmlClsid)
	{
		CLSIDFromString(StringA((char*)xmlClsid), &trainerId);
	}

	return S_OK;
}

result CSerializeConfig::ParseArgument(const StringA& value, const StringA& type, MinCOM::CommonVariant& arg)
{

	if ( type == StringA("CE_UINT") )
	{

		arg.vt_ = MinCOM::CE_UINT;
		arg.uintVal_ = atoi(value.c_str());		

	} else if ( type == StringA("CE_R4") )
	{

		arg.vt_ = MinCOM::CE_R4;
		arg.fltVal_ = (float)atof(value.c_str());

	} else
        return SP_XML_E_WRONGARGUMENTTYPE;

	return S_OK;
}
