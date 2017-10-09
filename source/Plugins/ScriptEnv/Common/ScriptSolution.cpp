#include "StdAfx.h"
#include "ScriptSolution.h"

// IXMLStorageController implementations section
bool CScriptSolution::Serialize(IXMLDOMDocument* pXMLDom, bool bIsLoad)
{
	if (bIsLoad)
	{
		return CSolutionOperation_Serialize::Load(this, pXMLDom);
	} else
	{
		return CSolutionOperation_Serialize::Save(this, pXMLDom);
	}
}

