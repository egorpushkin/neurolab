//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: NeuroFactory.h
//	Description: Network elements container and processor declaration. 

#ifndef NEUROFACTORY_H__NETWORKIMPORT__INCLUDED_
#define NEUROFACTORY_H__NETWORKIMPORT__INCLUDED_

#include "../NetworkImport.h"

#include "../../BuilderElements/Common/Common.h"

// CNeuroFactory declaration
class CNeuroFactory 
	: public NetworkImportingKit::IElementsCollection
	, public NetworkImportingKit::INetworkProcessor
	, public NetworkImportingKit::IStructureBuilder
	, public BuilderElementsCommonKit::IFactoryControl	
	, public IStorageController
{
public:
	CNeuroFactory(void);
	virtual ~CNeuroFactory(void);

	//////////////////////////////////////////////////////////////////////////
	// Internal tools
	//////////////////////////////////////////////////////////////////////////
	NetworkImportingKit::CConnection* FindConnectionByPrevPtr(dword_ptr connection);
	void				EstablishConnectionsAfterSerialization();

	void				RemoveConnections(NetworkImportingKit::IElement* piElement);
	void				ReleaseElementsList();

public:
	//////////////////////////////////////////////////////////////////////////
	// IFactoryControl declarations section
	//////////////////////////////////////////////////////////////////////////
	void				SetBuilderElementsControls(
		BuilderElementsCommonKit::IGroupsContainer* piGroupsContainer,
		BuilderElementsCommonKit::IFunctionsFactory* piFunctionsFactory);

	//////////////////////////////////////////////////////////////////////////
	// IStructureBuilder declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual NetworkImportingKit::IElement*		AddElement(const StringA& sysName, bool registerElement = true);	
	virtual result			ConnectElements(
		NetworkImportingKit::IElement* piElementSrc, 
		NetworkImportingKit::IElement* piElementDest, uint connectionSize = 1);
	virtual NetworkImportingKit::CConnection*	CreateConnection(uint connectionSize = 1);

	virtual	result			RemoveElement(NetworkImportingKit::IElement* piElement);
	virtual result			DisconnectElements(
		NetworkImportingKit::IElement* piElementSrc, 
		NetworkImportingKit::IElement* piElementDest, bool removeAllConnections = true);
	virtual	result			ReleaseContent();

	virtual result			ApplyTransferFunction(
		NetworkImportingKit::IElement* piElement, const StringA& functionName);
	virtual result			LocateElement(
		NetworkImportingKit::IElement* piElement, uint positionX, uint positionY);

	virtual void			EstablishConnections();

	//////////////////////////////////////////////////////////////////////////
	// IElementsCollection declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual result			SelectElement(NetworkImportingKit::IElement* pElement, bool shift, bool ctrl);

	virtual uint			GetInputsCount();
	virtual uint			GetOutputsCount();

	NetworkImportingKit::IElementsEnumerator* GetElementsEnumerator();

	//////////////////////////////////////////////////////////////////////////
	// INetworkProcessor declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual result			ProcessNetwork();

	virtual void			SetInputData(const IDataFactory* piDataFactory);
	virtual void			SetOutputData(const IDataFactory* piDataFactory);

	virtual void			GetInputData(IDataFactory* piDataFactory);
	virtual void			GetOutputData(IDataFactory* piDataFactory);

	//////////////////////////////////////////////////////////////////////////
	// IStorageController declarations section
	//////////////////////////////////////////////////////////////////////////
	result					Serialize(FILEDev& fileDev, bool loading);

	//////////////////////////////////////////////////////////////////////////
	// ICommon declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	//////////////////////////////////////////////////////////////////////////
	// NetworkImportingKit::IElementsCollection members
	//////////////////////////////////////////////////////////////////////////
	IContainer<NetworkImportingKit::IElement*>*			piNetworkElements_;

	//////////////////////////////////////////////////////////////////////////
	// BuilderElementsCommonKit::IFactoryControl members
	//////////////////////////////////////////////////////////////////////////
	BuilderElementsCommonKit::IGroupsContainer*			piGroupsContainer_;
	BuilderElementsCommonKit::IFunctionsFactory*		piFunctionsFactory_;

	//////////////////////////////////////////////////////////////////////////
	// ICommon members
	//////////////////////////////////////////////////////////////////////////
	ulong					numRef_;
};

#endif // !NEUROFACTORY_H__NETWORKIMPORT__INCLUDED_
