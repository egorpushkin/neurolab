#include "../../Headers/CmnNetworkImportingLib.h"
#include "BuilderElements/Common/Common.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CCmnLayer::CCmnLayer()
	: piInputData_(NULL)
	, piOutputData_(NULL)
	, layerDimension_(0)
	, inputsCount_(0)
	, piDeltas_(NULL)
{
	CDataFactory* pDataFactory = new CDataFactory();
	pDataFactory->QueryInterface(IID_IDataFactory, (void**)&piInputData_);

	pDataFactory = new CDataFactory();
	pDataFactory->QueryInterface(IID_IDataFactory, (void**)&piOutputData_);

	pDataFactory = new CDataFactory();
	pDataFactory->QueryInterface(IID_IDataFactory, (void**)&piDeltas_);
}

CCmnLayer::~CCmnLayer()
{
	CustomReleaseWeights();

	if (piInputData_)
		piInputData_->Release();

	if (piOutputData_)
		piOutputData_->Release();

	if (piDeltas_)
		piDeltas_->Release();	
}

// Custom tools
void CCmnLayer::FlowLayerData()
{
	// Receiving IDataConnector interface
	IDataConnector* piDataConnector = QueryTool<ILayerControl, IDataConnector>::
		QueryInterface((ILayerControl*)this, IID_IDataConnector);

	IConnectionsFactory* piConnectionsFactory = 
		piDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);

	piDataConnector->Release();
    
	IDataFlow* piDataFlow = QueryTool<ILayerControl, IDataFlow>::
		QueryInterface((ILayerControl*)this, IID_IDataFlow);

	CDataFactory* pData = new CDataFactory;
	IDataFactory* piElementData = QueryTool<CDataFactory, IDataFactory>::
		QueryInterface(pData, IID_IDataFactory);

	int outputIndex = 0;

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		int dataLength = pConnection->pOpposite_->data_.GetDataLength();

		piDataFlow->GetElementData(piElementData);

		pConnection->pOpposite_->data_.SetData(
			piElementData->GetData() + outputIndex, dataLength);

		outputIndex += dataLength;

		pConnection->pOpposite_->hasData_ = true;
	}
	piConnectionsEnum->Release();

	piElementData->Release();

	piConnectionsFactory->Release();

	piDataFlow->Release();
}

void CCmnLayer::ProcessLayer()
{
	if (piInputData_->GetDataLength() != inputsCount_ || 
		layerWeights_.size() != inputsCount_)
		return;

	IDataFlow* piDataFlow = QueryTool<ILayerControl, IDataFlow>::
		QueryInterface((ILayerControl*)this, IID_IDataFlow);

	const TransferFunction* pActivateFunction = piDataFlow->GetElementFunction();
	if (!pActivateFunction)
		return;

	piDataFlow->Release();
	
	for (uint i = 0;i < layerDimension_;i++)
	{
		for (uint j = 0;j < inputsCount_;j++)
			piOutputData_->IncreaseValue(
				i, 
				layerWeights_.at(j)->GetItemData(i) * piInputData_->GetItemData(j)
			);

		piOutputData_->SetItemData(
			i, 
			(*pActivateFunction->pProcesTransferFunction_)(
				pActivateFunction, 
				piOutputData_->GetItemData(i)
			)
		); 
	}	
}

// Custom allocation tools
void CCmnLayer::CustomCreateWeights(uint inputsCount, uint layerDimension)
{
	if (layerWeights_.size() > 0 && layerDimension_ > 0 && inputsCount_ > 0)
		CustomReleaseWeights();

	layerDimension_ = layerDimension;
	inputsCount_ = inputsCount;

	layerWeights_.reserve(inputsCount_);	
	for (uint i = 0;i < inputsCount_;i++)
	{
		CDataFactory* pFactory = new CDataFactory;
		IDataFactory* piFactory = QueryTool<CDataFactory, IDataFactory>::
			QueryInterface(pFactory, IID_IDataFactory);

		piFactory->CreateFactory(layerDimension_);

		layerWeights_.push_back(piFactory);
	}

	piInputData_->CreateFactory(layerDimension_);
	piOutputData_->CreateFactory(layerDimension_);

	piDeltas_->CreateFactory(layerDimension_);

	IDataFlow* piDataFlow = QueryTool<ILayerControl, IDataFlow>::
		QueryInterface((ILayerControl*)this, IID_IDataFlow);

	IDataFactory* piElementData = piDataFlow->GetDataFactory();
	piElementData->CreateFactory(layerDimension_);
	piElementData->Release();

	piDataFlow->Release();
}

void CCmnLayer::CustomReleaseWeights()
{
	for (uint i = 0;i < layerWeights_.size();i++)
		layerWeights_.at(i)->Release();
	layerWeights_.clear();
	
	layerDimension_ = 0;
	inputsCount_ = 0;   

	piInputData_->ReleaseFactory();
	piOutputData_->ReleaseFactory();

	piDeltas_->ReleaseFactory();
}

// IStorageController declarations section
result CCmnLayer::Serialize(FILEDev& fileDev, bool loading)
{
	if (loading)
	{	
		fileDev.Read(&layerDimension_, sizeof(uint));				
		fileDev.Read(&inputsCount_, sizeof(uint));	

		IStorageController* piStorage = NULL;

		piStorage = QueryTool<IDataFactory, IStorageController>::
			QueryInterface(piInputData_, IID_IStorageController);		
		piStorage->Serialize(fileDev, loading);
		piStorage->Release();

		piStorage = QueryTool<IDataFactory, IStorageController>::
			QueryInterface(piOutputData_, IID_IStorageController);
		piStorage->Serialize(fileDev, loading);
		piStorage->Release();		

		uint prevPtr = (uint)NULL;
		fileDev.Read(&prevPtr, sizeof(uint));
		if (prevPtr)
		{
			CustomCreateWeights(inputsCount_, layerDimension_);

			for (uint i = 0;i < inputsCount_;i++)
			{
				piStorage = QueryTool<IDataFactory, IStorageController>::
					QueryInterface(layerWeights_.at(i), IID_IStorageController);
				piStorage->Serialize(fileDev, loading);
				piStorage->Release();
			}
		}
	} else
	{			
		fileDev.Write(&layerDimension_, sizeof(uint));
		fileDev.Write(&inputsCount_, sizeof(uint));

		IStorageController* piStorage = NULL;

		piStorage = QueryTool<IDataFactory, IStorageController>::
			QueryInterface(piInputData_, IID_IStorageController);	
		piStorage->Serialize(fileDev, loading);
		piStorage->Release();

		piStorage = QueryTool<IDataFactory, IStorageController>::
			QueryInterface(piOutputData_, IID_IStorageController);
		piStorage->Serialize(fileDev, loading);
		piStorage->Release();	

		uint layerSize = (uint)layerWeights_.size();
		fileDev.Write(&layerSize, sizeof(uint));
		if (layerWeights_.size() > 0)
			for (uint i = 0;i < inputsCount_;i++)
			{
				piStorage = QueryTool<IDataFactory, IStorageController>::
					QueryInterface(layerWeights_.at(i), IID_IStorageController);
				piStorage->Serialize(fileDev, loading);
				piStorage->Release();
			}
	}

	return S_OK;
}

// ILayerControl implementations section
void CCmnLayer::SetInputData(const IDataFactory* piData)
{
	piInputData_->SetData(piData->GetData(), piData->GetDataLength());
}

void CCmnLayer::SetOutputData(const IDataFactory* piData)
{
	piOutputData_->SetData(piData->GetData(), piData->GetDataLength());
}

void CCmnLayer::GetInputData(IDataFactory* piData) const
{
	piData->SetData(piInputData_->GetData(), piInputData_->GetDataLength());
}

void CCmnLayer::GetOutputData(IDataFactory* piData) const
{
	piData->SetData(piOutputData_->GetData(), piOutputData_->GetDataLength());
}

void CCmnLayer::CreateWeights(uint inputsCount, uint layerDimension)
{
	CustomCreateWeights(inputsCount, layerDimension);
}

void CCmnLayer::ReleaseWeights()
{
	CustomReleaseWeights();
}

bool CCmnLayer::ModifyWeights()
{
	return false;
}

void CCmnLayer::ResetWeights(float value)
{
	for (uint i = 0;i < layerWeights_.size();i++)
		layerWeights_.at(i)->FillFactory(value);
}

uint CCmnLayer::GetDimension() const
{
	return layerDimension_;
}

uint CCmnLayer::GetInputsCount() const
{
	return inputsCount_;
}

float CCmnLayer::GetWeight(uint input, uint neuron) const
{
	if (input >= inputsCount_ || 
		neuron >= layerDimension_ || 
		input >= layerWeights_.size())
		return 0;

	return layerWeights_.at(input)->GetItemData(neuron);	
}

void CCmnLayer::SetWeight(uint input, uint neuron, float weightValue)
{
	if (input >= inputsCount_ || 
		neuron >= layerDimension_ || 
		input >= layerWeights_.size())
		return;

	layerWeights_.at(input)->SetItemData(neuron, weightValue);	
}

void CCmnLayer::SetDelta(uint neuron, float deltaValue)
{
	piDeltas_->SetItemData(neuron, deltaValue);
}

float CCmnLayer::GetDelta(uint neuron) const
{
	return piDeltas_->GetItemData(neuron);
}
