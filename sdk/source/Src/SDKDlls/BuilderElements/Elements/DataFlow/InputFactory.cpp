#include "InputFactory.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CInputFactory::CInputFactory(void)
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
	elementType_ = ET_INPUT;
	sysName_ = "InputFactory";
	sysTitle_ = "Input Factory";	
	sysShortName_ = "IF";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_DF_INPUT_FACTORY_MENU_ITEM;
	layerBehaviour_ = true;
	elementTextureActive_ = _T("Input_Factory_Active");
	elementTexturePassive_ = _T("Input_Factory_Passive");
	imageWidth_ = SIZE_LAYER_IMAGE_WIDTH;
	imageHeight_ = SIZE_LAYER_IMAGE_HEIGHT;
	shortNameOffset_ = 10;
	nameOffset_ = 45;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

CInputFactory::~CInputFactory(void)
{
}

// Custom tools
void CInputFactory::PostInitialize()
{
	// Custom initializations
	CustomCreateWeights(
		ELEMENT_DEFAULT_INPUTS_COUNT, 
		ELEMENT_DEFAULT_NEURONS_COUNT);
}

void CInputFactory::CustomCreateWeights(uint inputsCount, uint layerDimension)
{
	CCmnDataFlow::piElementData_->CreateFactory(layerDimension);

	CCmnLayer::layerDimension_ = layerDimension;
	CCmnLayer::inputsCount_ = inputsCount;
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void CInputFactory::FlowData()
{
	CCmnLayer::FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section

// IStorageController implementations section
result CInputFactory::Serialize(FILEDev& fileDev, bool loading)
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
ulong CInputFactory::AddRef()
{
	return ++numRef_;						
}

ulong CInputFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CInputFactory::GetClassString() const
{
	return _T("CInputFactory");
}

result CInputFactory::QueryInterface(REFIID iid, void** ppObject)
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
