#pragma once

#include "..\LuaEngine\LuaExecuteTool.h"
#include "..\LuaExtension\NeuroApi.h"
#include "..\LuaExtension\GlobalStorage.h"

class CLuaProcessor
{
public:

	bool ProcessElement(
		CString&			ElementScript,
		IElement*			pElement,
		IDataFactory*		pInputData,
		IDataFactory*		pOutputData)
	{
		// Initializing global storage
		CLuaStorage_ThisElement::pElement = pElement;

		CLuaStorage_ThisElement::pInputData = pInputData;
		CLuaStorage_ThisElement::pOutputData = pOutputData;
				
		// Executing script
		CCmnLua tmLuaObject;
		tmLuaObject.SetString(ElementScript);
		bool bRet = tmLuaObject.ExecuteScript(neuroapi_lualibs);

		// Release resources
		CLuaStorage_FactoriesContainer::ReleaseContainer();

		return bRet;
	}

};