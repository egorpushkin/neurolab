#include "HopfieldLayer.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CHopfieldLayer::CHopfieldLayer(void)
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
	sysName_ = "HopfieldLayer";
	sysTitle_ = "Hopfield Layer";
	sysShortName_ = "HL";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_EP_HOPFIELD_LAYER_MENU_ITEM;
	layerBehaviour_ = true;
	elementTextureActive_ = _T("Hopfield_Layer_Active");
	elementTexturePassive_ = _T("Hopfield_Layer_Passive");
	imageWidth_ = SIZE_LAYER_IMAGE_WIDTH;
	imageHeight_ = SIZE_LAYER_IMAGE_HEIGHT;
	shortNameOffset_ = 10;
	nameOffset_ = 45;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

CHopfieldLayer::~CHopfieldLayer(void)
{	
}

// Custom tools
void CHopfieldLayer::PostInitialize()
{
	// Custom initializations
	CCmnLayer::CustomCreateWeights(
		ELEMENT_DEFAULT_INPUTS_COUNT, 
		ELEMENT_DEFAULT_NEURONS_COUNT);
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void CHopfieldLayer::ProcessElement()
{
	if (CCmnLayer::layerWeights_.size() != CCmnLayer::inputsCount_ || 
		(CCmnLayer::inputsCount_ != CCmnLayer::layerDimension_) || 
		(CCmnLayer::inputsCount_ != CCmnLayer::piInputData_->GetDataLength()))
		return;

	CCmnDataFlow::MergeConnectionsData(
		CCmnLayer::piInputData_, 
		DC_INPUTS_FACTORY);

	bool equals = false;
	while (!equals)
	{
		CCmnLayer::ProcessLayer();

		equals = true;
		for (uint i = 0;i < CCmnLayer::layerDimension_;i++)
			if (CCmnLayer::piInputData_->GetItemData(i) != 
				CCmnLayer::piOutputData_->GetItemData(i))
			{
				equals = false;
				break;
			}

		if (!equals)
			CCmnLayer::piInputData_->SetData(
			CCmnLayer::piOutputData_);
	}

	CCmnDataFlow::piElementData_->SetData(
		CCmnLayer::piOutputData_);	
}

void CHopfieldLayer::FlowData()
{
	CCmnLayer::FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section
bool CHopfieldLayer::ModifyWeights()
{
	if (CCmnLayer::layerWeights_.size() != CCmnLayer::inputsCount_ || 
		(CCmnLayer::inputsCount_ != CCmnLayer::layerDimension_) || 
		(CCmnLayer::inputsCount_ != CCmnLayer::piInputData_->GetDataLength()))
		return false;

	for (uint i = 0;i < CCmnLayer::layerDimension_;i++)
		for (uint j = 0;j < CCmnLayer::layerDimension_;j++)
		{
			if (i == j)
			{
				//CCmnLayer::layerWeights_.at(i)->SetItemData(j, 0.0f);
                CCmnLayer::layerWeights_[i]->SetItemData(j, 0.0f);
				continue;
			}

			//CCmnLayer::layerWeights_.at(i)->IncreaseValue(j, 
            CCmnLayer::layerWeights_[i]->IncreaseValue(j, 
				CCmnLayer::piInputData_->GetItemData(i) * 
					CCmnLayer::piInputData_->GetItemData(j));
		}

    return true;
}

// IStorageController implementations section
result CHopfieldLayer::Serialize(FILEDev& fileDev, bool loading)
{
	CCmnElement::Serialize(fileDev, loading);
	CCmnBuilderElement::Serialize(fileDev, loading);
	CCmnDataFlow::Serialize(fileDev, loading);
	CCmnDataConnector::Serialize(fileDev, loading);
	CCmnLayer::Serialize(fileDev, loading);

	if (loading)
	{} else	{}

	return S_OK;
}

// ICommon implementations section
ulong CHopfieldLayer::AddRef()
{
	return ++numRef_;						
}

ulong CHopfieldLayer::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CHopfieldLayer::GetClassString() const
{
	return _T("CHopfieldLayer");
}

result CHopfieldLayer::QueryInterface(REFIID iid, void** ppObject)
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
