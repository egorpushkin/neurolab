#include "OutputFactory.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

COutputFactory::COutputFactory(void)
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
	elementType_ = ET_OUTPUT;
	sysName_ = "OutputFactory";
	sysTitle_ = "Output Factory";	
	sysShortName_ = "OF";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_DF_OUTPUT_FACTORY_MENU_ITEM;
	layerBehaviour_ = true;
	elementTextureActive_ = _T("Output_Factory_Active");
	elementTexturePassive_ = _T("Output_Factory_Passive");
	imageWidth_ = SIZE_LAYER_IMAGE_WIDTH;
	imageHeight_ = SIZE_LAYER_IMAGE_HEIGHT;
	shortNameOffset_ = 10;
	nameOffset_ = 45;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

COutputFactory::~COutputFactory(void)
{
}

// Custom tools
void COutputFactory::PostInitialize()
{
	// Custom initializations
	CustomCreateWeights(
		ELEMENT_DEFAULT_INPUTS_COUNT, 
		ELEMENT_DEFAULT_NEURONS_COUNT);
}

void COutputFactory::CustomCreateWeights(uint inputsCount, uint layerDimension)
{
	CCmnDataFlow::piElementData_->CreateFactory(layerDimension);

	CCmnLayer::layerDimension_ = layerDimension;
	CCmnLayer::inputsCount_ = inputsCount;
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void COutputFactory::ProcessElement()
{
	CCmnDataFlow::MergeConnectionsData(
		CCmnLayer::piInputData_, 
		DC_INPUTS_FACTORY);

	if (CCmnLayer::piInputData_->GetDataLength() != 
		CCmnDataFlow::piElementData_->GetDataLength())
		return;

	CCmnDataFlow::piElementData_->SetData(
		CCmnLayer::piInputData_);	
}

// IDataConnector implementations section

// ILayerCOntrol implementations section

// IStorageController implementations section
result COutputFactory::Serialize(FILEDev& fileDev, bool loading)
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
ulong COutputFactory::AddRef()
{
	return ++numRef_;						
}

ulong COutputFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String COutputFactory::GetClassString() const
{
	return _T("COutputFactory");
}

result COutputFactory::QueryInterface(REFIID iid, void** ppObject)
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
