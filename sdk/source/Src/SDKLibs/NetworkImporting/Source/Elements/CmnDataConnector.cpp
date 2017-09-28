#include "../../Headers/CmnNetworkImportingLib.h"
#include "BuilderElements/Common/Common.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CCmnDataConnector::CCmnDataConnector()
	: piInputsFactory_(NULL)
	, piOutputsFactory_(NULL)
	, addConnectionState_(DEFAULT_ADD_CONNECTION_STATE)
	, connectionsCount_(DEFAULT_CONNECTIONS_COUNT)
{
	CConnectionsFactory* pConnectionsFactory = new CConnectionsFactory;
	pConnectionsFactory->QueryInterface(IID_IConnectionsFactory, (void**)&piInputsFactory_);
	
	pConnectionsFactory = new CConnectionsFactory;
	pConnectionsFactory->QueryInterface(IID_IConnectionsFactory, (void**)&piOutputsFactory_);
}

CCmnDataConnector::~CCmnDataConnector()
{
	if (piInputsFactory_)
		piInputsFactory_->Release();
	if (piOutputsFactory_)
		piOutputsFactory_->Release();
}

// IStorageController implementations section
result CCmnDataConnector::Serialize(FILEDev& fileDev, bool loading)
{
	IStorageController* piStorage;
	
	piInputsFactory_->QueryInterface(IID_IStorageController, (void**)&piStorage);
	piStorage->Serialize(fileDev, loading);
	piStorage->Release();

	piOutputsFactory_->QueryInterface(IID_IStorageController, (void**)&piStorage);
	piStorage->Serialize(fileDev, loading);
	piStorage->Release();

	return S_OK;
}

// IDataConnector implementations section
result CCmnDataConnector::AddConnectionTo(IElement* piElement, uint factoryType)
{
	// Adding direct connection
	CConnection* pConnection = new CConnection(connectionsCount_);
	pConnection->piElement_ = piElement;
	
	IElement* piThisElement = QueryTool<IDataConnector, IElement>::
		QueryInterface((IDataConnector*)this, IID_IElement);
	
	pConnection->pOpposite_ = (CConnection*)piThisElement;
	pConnection->prevPtr_ = (dword_ptr)NULL;
	pConnection->prevOpositePtr_ = (dword_ptr)factoryType;

	piThisElement->Release();

	IConnectionsFactory* piConnectionsFactory = GetConnectionsFactory(factoryType);
	piConnectionsFactory->AddConnection(pConnection);
	piConnectionsFactory->Release();

	return S_OK;
}

void CCmnDataConnector::RemoveConnection(CConnection* pConnection)
{
	IConnectionsFactory* piConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);
	piConnectionsFactory->RemoveConnection(pConnection);
	piConnectionsFactory->Release();

	piConnectionsFactory = GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	piConnectionsFactory->RemoveConnection(pConnection);
	piConnectionsFactory->Release();
}

void CCmnDataConnector::SetAddConnectionState(uint state, uint count)
{
	addConnectionState_ = state;
	connectionsCount_ = count;
}

result CCmnDataConnector::ProcessAddConnection(IElement* piElement)
{
	// checking whether connection can be established
	IElement* piFromElement = QueryTool<IDataConnector, IElement>::
		QueryInterface((IDataConnector*)this, IID_IElement);

	IElement* piToElement = piElement;

	if (piFromElement == piToElement)
	{
		piFromElement->Release();
		return NI_E_CANNOTCONNECT;	
	}

	if (piFromElement->GetElementType() == ET_INPUT &&
		addConnectionState_ == DC_INPUTS_FACTORY)
	{
		piFromElement->Release();
		return NI_E_CANNOTCONNECT;
	}

	if (piFromElement->GetElementType() == ET_OUTPUT &&
		addConnectionState_ == DC_OUTPUTS_FACTORY)
	{
		piFromElement->Release();
		return NI_E_CANNOTCONNECT;
	}

	if (piToElement->GetElementType() == ET_INPUT &&
		addConnectionState_ == DC_OUTPUTS_FACTORY)
	{
		piFromElement->Release();
		return NI_E_CANNOTCONNECT;
	}

	if (piToElement->GetElementType() == ET_OUTPUT &&
		addConnectionState_ == DC_INPUTS_FACTORY)
	{
		piFromElement->Release();
		return NI_E_CANNOTCONNECT;
	}

	piFromElement->Release();

	result resultCode = AddConnectionTo(piToElement, addConnectionState_);

	addConnectionState_ = DEFAULT_ADD_CONNECTION_STATE;

	return resultCode;
}

bool CCmnDataConnector::MoveConnection(const CConnection* pConnection, bool moveUp)
{
	IConnectionsFactory* piConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);
	bool retCode = piConnectionsFactory->MoveConnection(pConnection, moveUp);
	piConnectionsFactory->Release();

	piConnectionsFactory = GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	retCode |= piConnectionsFactory->MoveConnection(pConnection, moveUp);
	piConnectionsFactory->Release();

	return retCode;
}

IConnectionsFactory* CCmnDataConnector::GetConnectionsFactory(uint factoryType) const
{
	IConnectionsFactory* piFactory = NULL;
	switch (factoryType)
	{
	case DC_INPUTS_FACTORY:
		piFactory = piInputsFactory_;
		break;
	case DC_OUTPUTS_FACTORY:
		piFactory = piOutputsFactory_;
		break;
	}	

	if (piFactory)
		piFactory->AddRef();

	return piFactory;
}

CConnection* CCmnDataConnector::FindConnectionByPrevPtr(dword_ptr connection)
{
	CConnection* pFoundConnection = piInputsFactory_->FindConnectionByPrevPtr(connection);
	if (pFoundConnection)
		return pFoundConnection;

	pFoundConnection = piOutputsFactory_->FindConnectionByPrevPtr(connection);
	if (pFoundConnection)
		return pFoundConnection;

	return NULL;
}


