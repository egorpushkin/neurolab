#include "RBFLayer.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CRBFLayer::CRBFLayer(void)
	// Base class constructors invocation
	: CCmnElement()
	, CCmnBuilderElement()
	, CCmnDataFlow()
	, CCmnDataConnector()
	, CCmnLayer()
	// ICommon  data fields initialization
	, numRef_(0)
{	
	// IElement data fields initialization (declared in CCmnElement wrapper)
	elementType_ = ET_PROCESSOR;
	sysName_ = "RBFLayer";
	sysTitle_ = "RBF Layer";
	sysShortName_ = "RBFL";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_EP_RBF_LAYER_MENU_ITEM;
	layerBehaviour_ = true;
	elementTextureActive_ = _T("RBF_Layer_Active");
	elementTexturePassive_ = _T("RBF_Layer_Passive");
	imageWidth_ = SIZE_LAYER_IMAGE_WIDTH;
	imageHeight_ = SIZE_LAYER_IMAGE_HEIGHT;
	shortNameOffset_ = 17;
	nameOffset_ = 29;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

CRBFLayer::~CRBFLayer(void)
{
}

// Custom tools
void CRBFLayer::PostInitialize()
{
	// Custom initializations
	CCmnLayer::CustomCreateWeights(
		ELEMENT_DEFAULT_INPUTS_COUNT, 
		ELEMENT_DEFAULT_NEURONS_COUNT);
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void CRBFLayer::ProcessElement()
{
	CCmnDataFlow::MergeConnectionsData(
		CCmnLayer::piInputData_, 
		DC_INPUTS_FACTORY);

	if (CCmnLayer::piInputData_->GetDataLength() != CCmnLayer::inputsCount_)
		return;
	if ((CCmnLayer::piOutputData_->GetDataLength() != CCmnLayer::layerDimension_) ||
		(CCmnDataFlow::piElementData_->GetDataLength() != CCmnLayer::layerDimension_))
		return;

	for (uint i = 0;i < CCmnLayer::layerDimension_;i++)
	{
		float cellCenter = 0.0f;
		
		for (uint j = 0;j < CCmnLayer::inputsCount_;j++)
			cellCenter += 
				//(CCmnLayer::layerWeights_.at(j)->GetItemData(i) - CCmnLayer::piInputData_->GetItemData(j)) *
				//(CCmnLayer::layerWeights_.at(j)->GetItemData(i) - CCmnLayer::piInputData_->GetItemData(j));
                (CCmnLayer::layerWeights_[j]->GetItemData(i) - CCmnLayer::piInputData_->GetItemData(j)) *
                (CCmnLayer::layerWeights_[j]->GetItemData(i) - CCmnLayer::piInputData_->GetItemData(j));	

		cellCenter *= -1;

		float cellDelta = CCmnLayer::piDeltas_->GetItemData(i);
	
		float cellOut = cellCenter;
		if (cellDelta != 0)
			cellOut /= (cellDelta * cellDelta);
		if (CCmnDataFlow::pActivateFunction_)
			cellOut = (*CCmnDataFlow::pActivateFunction_->pProcesTransferFunction_)(CCmnDataFlow::pActivateFunction_, cellOut);

		CCmnLayer::piOutputData_->SetItemData(i, cellOut);
	}

	CCmnDataFlow::piElementData_->SetData(
		CCmnLayer::piOutputData_);	
}

void CRBFLayer::FlowData()
{
	CCmnLayer::FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section

// IStorageController implementations section
result CRBFLayer::Serialize(FILEDev& fileDev, bool loading)
{
	CCmnElement::Serialize(fileDev, loading);
	CCmnBuilderElement::Serialize(fileDev, loading);
	CCmnDataFlow::Serialize(fileDev, loading);
	CCmnDataConnector::Serialize(fileDev, loading);
	CCmnLayer::Serialize(fileDev, loading);

	// Serializing layer deltas 
	IStorageController* piStorageController = 
		QueryTool<IDataFactory, IStorageController>::
			QueryInterface(CCmnLayer::piDeltas_, IID_IStorageController);
	
	piStorageController->Serialize(fileDev, loading);

	piStorageController->Release();

	if (loading)
	{} else	{}

	return S_OK;
}

// ICommon implementations section
ulong CRBFLayer::AddRef()
{
	return ++numRef_;						
}

ulong CRBFLayer::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CRBFLayer::GetClassString() const
{
	return _T("CRBFLayer");
}

result CRBFLayer::QueryInterface(REFIID iid, void** ppObject)
{
	if (iid == IID_ICommon)
	{		
		*ppObject = (ICommon*)(IElement*)this;
	}
	else if (iid == IID_IElement)
	{
		*ppObject = (IElement*)this;
	}
	else if (iid == IID_IBuilderElement)
	{
		*ppObject = (IBuilderElement*)this;
	}
	else if (iid == IID_IDataFlow)
	{
		*ppObject = (IDataFlow*)this;
	}
	else if (iid == IID_IDataConnector)
	{
		*ppObject = (IDataConnector*)this;
	}
	else if (iid == IID_ILayerControl)
	{
		*ppObject = (ILayerControl*)this;
	}
	else if (iid == IID_IStorageController)
	{
		*ppObject = (IStorageController*)(CCmnElement*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)(IElement*)this)->AddRef();
	return S_OK;
}
