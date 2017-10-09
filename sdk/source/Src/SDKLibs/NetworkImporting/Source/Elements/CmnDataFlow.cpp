#include "../../Headers/CmnNetworkImportingLib.h"
#include "BuilderElements/Common/Common.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CCmnDataFlow::CCmnDataFlow()
	: pActivateFunction_(NULL)	
	, functionName_("")
	, piElementData_(NULL)
{
	CDataFactory* pElementData = new CDataFactory;
	pElementData->QueryInterface(IID_IDataFactory, (void**)&piElementData_);
}

CCmnDataFlow::~CCmnDataFlow()
{
	if (piElementData_)
		piElementData_->Release();
}

// Custom tools
bool CCmnDataFlow::GetFactoryReadyState(uint factoryType)
{
	// Receiving IDataConnector interface
	IDataConnector* piDataConnector = QueryTool<IDataFlow, IDataConnector>::
		QueryInterface((IDataFlow*)this, IID_IDataConnector);
	
	// Receiving IConnectionsFactory interface for 'factoryType' connections factory
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(factoryType);
	assert(piConnectionsFactory != NULL);

	piDataConnector->Release();

	// Enumerating connections
	bool ready = true;

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); 
		hasConnections;
		hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		if (!pConnection->hasData_)
		{
			ready = false;
			break;
		}
	}
	piConnectionsEnum->Release();	

	piConnectionsFactory->Release();

	return ready;
}

// IStorageController declarations section
result CCmnDataFlow::Serialize(FILEDev& fileDev, bool loading)
{
	if (loading)
	{
		bool hasFunction;
		fileDev.Read(&hasFunction, sizeof(bool));
		if (hasFunction)
		{
			functionName_ = "";
			fileDev.ReadStringA(functionName_);
		}

		IStorageController* piStorage = QueryTool<IDataFactory, IStorageController>::
			QueryInterface(piElementData_, IID_IStorageController);

		piStorage->Serialize(fileDev, loading);

		piStorage->Release();
	} else
	{			
		bool hasFunction = true;
		if (!pActivateFunction_)
			hasFunction = false;

		fileDev.Write(&hasFunction, sizeof(bool));

		if (hasFunction)
			fileDev.WriteStringA(pActivateFunction_->name_);

		IStorageController* piStorage = QueryTool<IDataFactory, IStorageController>::
			QueryInterface(piElementData_, IID_IStorageController);

		piStorage->Serialize(fileDev, loading);

		piStorage->Release();
	}

	return S_OK;
}

// IDataFlow declarations section
const TransferFunction* CCmnDataFlow::GetElementFunction() const
{
	return pActivateFunction_;
}

void CCmnDataFlow::SetElementFunction(TransferFunction* pFunction)
{
	pActivateFunction_ = pFunction;

	if (pActivateFunction_)
		functionName_ = pActivateFunction_->name_;
	else 
		functionName_ = "";
}

const StringA& CCmnDataFlow::GetFunctionName() const
{
	return functionName_;
}

bool CCmnDataFlow::RequireData() const
{
	return true;
}

void CCmnDataFlow::SetWaitDataState()
{
	// Receiving IDataConnector interface
	IDataConnector* piDataConnector = QueryTool<IDataFlow, IDataConnector>::
		QueryInterface((IDataFlow*)this, IID_IDataConnector);

	// Receiving IConnectionsFactory interface for DC_INPUTS_FACTORY connections factory
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
	assert(piConnectionsFactory != NULL);

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		pConnection->hasData_ = false;
	}
	piConnectionsEnum->Release();	

	piConnectionsFactory->Release();

	// Receiving IConnectionsFactory interface for DC_OUTPUTS_FACTORY connections factory
	piConnectionsFactory = piDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	assert(piConnectionsFactory != NULL);

	piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		pConnection->hasData_ = false;
	}
	piConnectionsEnum->Release();	

	piConnectionsFactory->Release();

	piDataConnector->Release();
}

bool CCmnDataFlow::IsReadyForProcessing()
{
	return GetFactoryReadyState(DC_INPUTS_FACTORY);
}

void CCmnDataFlow::FlowData()
{
	// Receiving IDataConnector interface
	IDataConnector* piDataConnector = QueryTool<IDataFlow, IDataConnector>::
		QueryInterface((IDataFlow*)this, IID_IDataConnector);
	
	// Receiving IConnectionsFactory interface for DC_OUTPUTS_FACTORY connections factory
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	assert(piConnectionsFactory != NULL);

	piDataConnector->Release();

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();
		assert(pConnection->pOpposite_ != NULL);

		pConnection->pOpposite_->hasData_ = true;
		pConnection->pOpposite_->data_.FillFactory(piElementData_->GetItemData(0));
	}
	piConnectionsEnum->Release();	

	piConnectionsFactory->Release();
}

void CCmnDataFlow::ProcessElement()
{
}

bool CCmnDataFlow::IsReadyForTraining()
{
	return GetFactoryReadyState(DC_OUTPUTS_FACTORY);
}

void CCmnDataFlow::BackFlow()
{
	// Receiving IDataConnector interface
	IDataConnector* piDataConnector = QueryTool<IDataFlow, IDataConnector>::
		QueryInterface((IDataFlow*)this, IID_IDataConnector);

	// Receiving IConnectionsFactory interface for DC_INPUTS_FACTORY connections factory
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
	assert(piConnectionsFactory != NULL);

	piDataConnector->Release();

	IConnectionsEnumerator* piConnectionsEnum = 
		piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();
		assert(pConnection->pOpposite_ != NULL);

		pConnection->pOpposite_->hasData_ = true;
	}
	piConnectionsEnum->Release();	

	piConnectionsFactory->Release();
}

void CCmnDataFlow::GetElementData(IDataFactory* piData) const
{
	piData->SetData(piElementData_->GetData(), piElementData_->GetDataLength());
}

void CCmnDataFlow::SetElementData(const IDataFactory* piData)
{
	piElementData_->SetData(piData->GetData(), piData->GetDataLength());
}

IDataFactory* CCmnDataFlow::GetDataFactory() const
{
	piElementData_->AddRef();

    return piElementData_;	
}

void CCmnDataFlow::MergeConnectionsData(IDataFactory* piData, uint factoryType)
{
	// Receiving IDataConnector interface
	IDataConnector* piDataConnector = QueryTool<IDataFlow, IDataConnector>::
		QueryInterface((IDataFlow*)this, IID_IDataConnector);

	// Receiving IConnectionsFactory interface for 'factoryType' connections factory
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(factoryType);

	piDataConnector->Release();

	// Calculating data length
	uint dataLength = 0;

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		dataLength += pConnection->data_.GetDataLength();
	}
	piConnectionsEnum->Release();	

	if (piData->GetDataLength() != dataLength)
		piData->CreateFactory(dataLength);

	// Merging data
	uint dataOffset = 0;
    
	piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		memcpy(piData->GetData() + dataOffset, 
			pConnection->data_.GetData(), 
			pConnection->data_.GetDataLength() * sizeof(float));

		dataOffset += pConnection->data_.GetDataLength();
	}
	piConnectionsEnum->Release();	

	piConnectionsFactory->Release();
}
