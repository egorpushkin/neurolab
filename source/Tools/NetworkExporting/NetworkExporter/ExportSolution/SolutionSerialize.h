#pragma once

#include "CmnXML.h"

class CExportGroup;
class CExportSolution;
#include "ExportSolution.h"

class CSolutionSerialize
{
public:
	static bool LoadSolution(CExportSolution* pSolution);
	static bool VerifySolution(CExportSolution* pExportSolution);

private:
	static bool VerifyRootSymbol(IXMLDOMDocument* pXMLDom);
	static bool EnumerateGroups(CExportSolution* pSolution, IXMLDOMDocument* pXMLDom);
	static bool EnumerateItems(CExportGroup* pExportGroup, IXMLDOMNode* pXMLGroupNode);
};
