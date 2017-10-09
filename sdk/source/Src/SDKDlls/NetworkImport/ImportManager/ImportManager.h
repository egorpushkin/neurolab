//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ImportManager.h
//	Description: Import Manager component declaration.  

#ifndef IMPORTMANAGER_H__NETWORKIMPORT__INCLUDED_
#define IMPORTMANAGER_H__NETWORKIMPORT__INCLUDED_

#include "../NetworkImport.h"

#include "../../BuilderElements/Common/Common.h"

class CImportManager 
	: public NetworkImportingKit::IImportManager
{
public:
	CImportManager();
	virtual ~CImportManager();

	// IImportManager declarations section	
	virtual result			InitializeManager();
	virtual result			LoadNLProject(
		const StringA& rFileName, 
		NetworkImportingKit::INetworkProcessor** ppNetProc);	
	virtual result			StoreNLProject(
		const StringA& fileName, 
		NetworkImportingKit::INetworkProcessor* piNetProc);	
	virtual result			CreateEmptyNetwork(
		NetworkImportingKit::INetworkProcessor** ppiNetProc);

	// ICommon declarations section	
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	BuilderElementsCommonKit::IGroupsContainer*		piGroupsContainer_;	
	BuilderElementsCommonKit::IFunctionsFactory*	piFunctionsFactory_;

	IComponentLoader*		piBuilderElementsComponent_;

    bool					initialized_;

	ulong					numRef_;
};

#endif // !IMPORTMANAGER_H__NETWORKIMPORT__INCLUDED_
