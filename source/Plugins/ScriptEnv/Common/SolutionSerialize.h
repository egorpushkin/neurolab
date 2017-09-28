#pragma once

class CScriptSolution;
#include "ScriptSolution.h"

class CSolutionOperation_Serialize
{
public:
	// Storing Solution
	static bool Save(CScriptSolution* pSolution, IXMLDOMDocument* pXMLDom);
	static bool AddItems(CScriptSolution* pSolution, IXMLDOMElement* pXMLElement, IXMLDOMDocument* pXMLDom);
	static bool AddDataItems(CScriptSolution* pSolution, IXMLDOMElement* pXMLElement, IXMLDOMDocument* pXMLDom);
	static bool AddBitmaps(CScriptSolution* pSolution, IXMLDOMElement* pXMLElement, IXMLDOMDocument* pXMLDom);
	static bool AddProjects(CScriptSolution* pSolution, IXMLDOMElement* pXMLElement, IXMLDOMDocument* pXMLDom);

	// Loading Solution
	static bool Load(CScriptSolution* pSolution, IXMLDOMDocument* pXMLDom);
};