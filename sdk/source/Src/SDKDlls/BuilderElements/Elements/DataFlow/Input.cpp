#include "Input.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CInput::CInput(void)
	// Base class constructors invocation
	: CCmnElement()
	, CCmnBuilderElement()
	, CCmnDataFlow()
	, CCmnDataConnector()
	// ICommon  data fields initialization
	, numRef_(0)
{	
	// IElement data fields initialization (declared in CCmnElement wrapper)
	elementType_ = ET_INPUT;
	sysName_ = "Input";
	sysTitle_ = "Input";	
	sysShortName_ = "I";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_DF_INPUT_MENU_ITEM;
	layerBehaviour_ = false;
	elementTextureActive_ = _T("Input_Active");
	elementTexturePassive_ = _T("Output_Passive");
	imageWidth_ = SIZE_INPUT_IMAGE_DIAMETER;
	imageHeight_ = SIZE_INPUT_IMAGE_DIAMETER;
	shortNameOffset_ = 8;
	nameOffset_ = 0;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

CInput::~CInput(void)
{
}

// Custom tools
void CInput::PostInitialize()
{
	CCmnDataFlow::piElementData_->CreateFactory(
		DEFAULT_ELEMENT_DATA_LENGTH);
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section

// IDataConnector implementations section

// IStorageController implementations section
result CInput::Serialize(FILEDev& fileDev, bool loading)
{
	CCmnElement::Serialize(fileDev, loading);
	CCmnBuilderElement::Serialize(fileDev, loading);
	CCmnDataFlow::Serialize(fileDev, loading);
	CCmnDataConnector::Serialize(fileDev, loading);

	if (loading)
	{} else	{}

	return S_OK;
}

// ICommon implementations section
ulong CInput::AddRef()
{
	return ++numRef_;						
}

ulong CInput::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CInput::GetClassString() const
{
	return _T("CInput");
}

result CInput::QueryInterface(REFIID iid, void** ppObject)
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
