#include "../PrecompiledHeader.h"

#include "XMLProjectParser.h"

using namespace Workspace;

namespace Serialization
{

XMLProjectParser::XMLProjectParser()
{	
}

XMLProjectParser::~XMLProjectParser()
{	
}

// Public interface
//////////////////////////////////////////////////////////////////////////
result XMLProjectParser::LoadProject(const StringA& fileName, Workspace::IAreasProject* piAreasProject)
{
	xmlDocPtr pDocument = xmlParseFile(fileName.c_str());
	if (!pDocument) 
		return STG_E_FILENOTFOUND;

	xmlNodePtr pNode = xmlDocGetRootElement(pDocument);
	if (!pNode)
	{			
		xmlFreeDoc(pDocument);
		return XML_E_NOROOT;
	}

	if (xmlStrcmp(pNode->name, (const xmlChar*)"AreasProject")) 
	{	
		xmlFreeDoc(pDocument);
		return XML_E_WRONGFORMAT;		
	}

	xmlChar* xmlProjectName = xmlGetProp(pNode, (const xmlChar *)"name");
	if (!xmlProjectName)
	{
		xmlFreeDoc(pDocument);
		return XML_E_WRONGFORMAT;	
	}

	piAreasProject->SetProjectName(StringA((char*)xmlProjectName));

	result resultCode = S_OK;
	
	pNode = pNode->xmlChildrenNode;
	while (pNode)
	{
		if (!xmlStrcmp(pNode->name, (const xmlChar*)"NetworkProject"))
		{
			resultCode = ParseProject(pNode, piAreasProject->GetNetworkProject());
			if (FAILED(resultCode))
				break;
		} else if (!xmlStrcmp(pNode->name, (const xmlChar*)"MultispecImage"))
		{
			resultCode = ParseImage(pNode, piAreasProject->GetMultispecImage());
			if (FAILED(resultCode))
				break;
		} else if (!xmlStrcmp(pNode->name, (const xmlChar*)"MapConfig"))
		{
			resultCode = ParseMapConfig(pNode, piAreasProject->GetMapConfig());
			if (FAILED(resultCode))
				break;
		}

		pNode = pNode->next;
	}

	xmlFreeDoc(pDocument);

	return resultCode;
}

// Private tools
//////////////////////////////////////////////////////////////////////////
result XMLProjectParser::ParseProject(xmlNodePtr pProjectNode, Workspace::NetworkProject* /* pProject */)
{	
	xmlChar* xmlProjectName = xmlGetProp(pProjectNode, (const xmlChar *)"name");
	xmlChar* xmlProjectFile = xmlGetProp(pProjectNode, (const xmlChar *)"file");

	if (!xmlProjectName || !xmlProjectFile)
		return XML_E_WRONGFORMAT;

	/* if (FAILED(pProject->LoadProject(StringA((char*)xmlProjectFile), StringA((char*)xmlProjectName))))
		return PROJECT_E_WRONGNETWORK; */

	return S_OK;
}

result XMLProjectParser::ParseImage(xmlNodePtr pImageNode, Workspace::MultispectralImage* pImage)
{
	xmlChar* xmlImageName = xmlGetProp(pImageNode, (const xmlChar *)"name");

	if (!xmlImageName)
		return XML_E_WRONGFORMAT;

	pImage->SetImageName(StringA((char*)xmlImageName));

	xmlNodePtr pBandNode = pImageNode->xmlChildrenNode;
	while (pBandNode)
	{
		if (!xmlStrcmp(pBandNode->name, (const xmlChar*)"Band"))
		{
			xmlChar* xmlBandName = xmlGetProp(pBandNode, (const xmlChar *)"name");
			xmlChar* xmlBandFile = xmlGetProp(pBandNode, (const xmlChar *)"file");

			if (xmlBandName && xmlBandFile)
			{
				if (FAILED(pImage->AddBand(StringA((char*)xmlBandFile), StringA((char*)xmlBandName))))
					return PROJECT_E_WRONGBAND;
			}
		}

		pBandNode = pBandNode->next;
	}	

	if (pImage->GetBandsCount() == 0)
		return XML_E_WRONGFORMAT;

	return S_OK;
}

result XMLProjectParser::ParseMapConfig(xmlNodePtr pMapConfigNode, Workspace::MapConfig* pMapConfig)
{
	xmlNodePtr pParameter = pMapConfigNode->xmlChildrenNode;
	while (pParameter)
	{
		if (!xmlStrcmp(pParameter->name, (const xmlChar*)"Parameter"))
		{
			xmlChar* xmlName = xmlGetProp(pParameter, (const xmlChar *)"name");
			xmlChar* xmlValue = xmlGetProp(pParameter, (const xmlChar *)"value");

			if (xmlName && xmlValue)
			{
				if (FAILED(pMapConfig->AddParameter(StringA((char*)xmlName), StringA((char*)xmlValue))))
					return PROJECT_E_WRONPARAMETER;
			}
		}

		pParameter = pParameter->next;
	}	

	if (pMapConfig->GetParametersCount() == 0)
		return XML_E_WRONGFORMAT;

	return S_OK;
}

}
