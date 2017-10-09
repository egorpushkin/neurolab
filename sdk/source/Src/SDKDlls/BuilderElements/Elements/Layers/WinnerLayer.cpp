#include "WinnerLayer.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CWinnerLayer::CWinnerLayer(void)
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
	sysName_ = "WinnerLayer";
	sysTitle_ = "Winner Layer";
	sysShortName_ = "WL";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_EP_WINNER_LAYER_MENU_ITEM;
	layerBehaviour_ = true;
	elementTextureActive_ = _T("Winner_Layer_Active");
	elementTexturePassive_ = _T("Winner_Layer_Passive");
	imageWidth_ = SIZE_LAYER_IMAGE_WIDTH;
	imageHeight_ = SIZE_LAYER_IMAGE_HEIGHT;
	shortNameOffset_ = 10;
	nameOffset_ = 45;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

CWinnerLayer::~CWinnerLayer(void)
{
}

// Custom tools
void CWinnerLayer::PostInitialize()
{
	// Custom initializations
	CustomCreateWeights(
		ELEMENT_DEFAULT_INPUTS_COUNT, 
		ELEMENT_DEFAULT_NEURONS_COUNT);
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void CWinnerLayer::ProcessElement()
{
	CCmnDataFlow::MergeConnectionsData(
		CCmnLayer::piInputData_, 
		DC_INPUTS_FACTORY);

	if (CCmnLayer::piInputData_->GetDataLength() != 
		CCmnDataFlow::piElementData_->GetDataLength())
		return;

	uint winnerIndex = 0;
	for (uint i = 1;i < CCmnLayer::piInputData_->GetDataLength();i++)
		if (CCmnLayer::piInputData_->GetItemData(i) > 
			CCmnLayer::piInputData_->GetItemData(winnerIndex))
			winnerIndex = i;

	for (uint i = 0;i < CCmnLayer::piInputData_->GetDataLength();i++)
		if (i == winnerIndex)
			CCmnLayer::piOutputData_->SetItemData(i, 1.0f);
		else
			CCmnLayer::piOutputData_->SetItemData(i, 0.0f);

	CCmnDataFlow::piElementData_->SetData(
		CCmnLayer::piOutputData_);	
}

void CWinnerLayer::FlowData()
{
	CCmnLayer::FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section

// IStorageController implementations section
result CWinnerLayer::Serialize(FILEDev& fileDev, bool loading)
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
ulong CWinnerLayer::AddRef()
{
	return ++numRef_;						
}

ulong CWinnerLayer::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CWinnerLayer::GetClassString() const
{
	return _T("CWinnerLayer");
}

result CWinnerLayer::QueryInterface(REFIID iid, void** ppObject)
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
