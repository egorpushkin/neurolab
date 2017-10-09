#pragma once

// Neuro Laboratory core object model headers
#include "CmnDataFile.h"
#include "CmnFactory.h"
#include "System\Directory.h"

class CLuaStorage_ThisElement
{
public:
	static IElement*			pElement;

	static IDataFactory*		pInputData;
	static IDataFactory*		pOutputData;
};

class CLuaStorage_FactoriesContainer
{
public:
	static bool RemoveFactory(IDataFactory* pDataFactory)
	{
		POSITION pos = mFactoriesList.Find(pDataFactory);
		if (!pos)
			return false;

		mFactoriesList.RemoveAt(pos);
		delete pDataFactory;

		return true;
	}

	static void AddFactory(IDataFactory* pDataFactory)
	{
		mFactoriesList.AddTail(pDataFactory);
	}    

	static void ReleaseContainer()
	{
		RELEASE_LIST(mFactoriesList, IDataFactory*, true)
	}

	static CList<IDataFactory*, IDataFactory*> mFactoriesList;
};