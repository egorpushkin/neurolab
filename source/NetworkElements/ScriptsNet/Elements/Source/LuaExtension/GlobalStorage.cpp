#include "StdAfx.h"
#include "GlobalStorage.h"

IElement*			CLuaStorage_ThisElement::pElement			= NULL;
IDataFactory*		CLuaStorage_ThisElement::pInputData			= NULL;
IDataFactory*		CLuaStorage_ThisElement::pOutputData		= NULL;

CList<IDataFactory*, IDataFactory*> CLuaStorage_FactoriesContainer::mFactoriesList;