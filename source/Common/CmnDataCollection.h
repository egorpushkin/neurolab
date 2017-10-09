#pragma once

#include "CmnObjects.h"

#include "DataCollection/CollectionDataArray.h"
#include "DataCollection/CollectionGroup.h"

interface IDataCollection : public IObject
{
	// State founctions
	virtual bool			IsCreated() = 0;

	// Creation/destruction functions
	virtual void			CreateCollection(CString& csName) = 0;
	virtual void			DestructCollection() = 0;

	// Save/Load operations
	virtual bool			LoadCollection(CString& FileName) = 0;
	virtual bool			SaveCollection(CString& FileName) = 0;

	// Properties
	virtual CString			GetCollectionName() = 0;
	virtual void			SetCollectionName(CString& Name) = 0;

	virtual CCollectionGroup* GetCollectionGroup() = 0;
	virtual CCollectionGroup* GetGroupByName(CString& Name) = 0;
};
