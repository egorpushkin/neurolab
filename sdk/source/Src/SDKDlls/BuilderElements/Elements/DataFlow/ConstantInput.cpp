#include "ConstantInput.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CConstantInput::CConstantInput(void)
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
	sysName_ = "ConstantInput";
	sysTitle_ = "Constant Input";	
	sysShortName_ = "CI";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_DF_CINPUT_MENU_ITEM;
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

CConstantInput::~CConstantInput(void)
{
}

// Custom tools
void CConstantInput::PostInitialize()
{
	CCmnDataFlow::piElementData_->CreateFactory(
		DEFAULT_ELEMENT_DATA_LENGTH,
		DEFAULT_CONSTANT_INPUT_VALUE);
}


// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
bool CConstantInput::RequireData() const
{
	return false;
}

// IDataConnector implementations section

// IStorageController implementations section
result CConstantInput::Serialize(FILEDev& fileDev, bool loading)
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
ulong CConstantInput::AddRef()
{
	return ++numRef_;						
}

ulong CConstantInput::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CConstantInput::GetClassString() const
{
	return _T("CConstantInput");
}

result CConstantInput::QueryInterface(REFIID iid, void** ppObject)
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
