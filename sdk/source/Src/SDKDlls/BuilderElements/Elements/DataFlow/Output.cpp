#include "Output.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

COutput::COutput(void)
	// Base class constructors invocation
	: CCmnElement()
	, CCmnBuilderElement()
	, CCmnDataFlow()
	, CCmnDataConnector()
	// ICommon  data fields initialization
	, numRef_(0)
{	
	// IElement data fields initialization (declared in CCmnElement wrapper)
	elementType_ = ET_OUTPUT;
	sysName_ = "Output";
	sysTitle_ = "Output";	
	sysShortName_ = "O";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_DF_OUTPUT_MENU_ITEM;
	layerBehaviour_ = false;
	elementTextureActive_ = _T("Output_Active");
	elementTexturePassive_ = _T("Output_Passive");
	imageWidth_ = SIZE_INPUT_IMAGE_DIAMETER;
	imageHeight_ = SIZE_INPUT_IMAGE_DIAMETER;
	shortNameOffset_ = 8;
	nameOffset_ = 0;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

COutput::~COutput(void)
{
}

// Custom tools
void COutput::PostInitialize()
{
	CCmnDataFlow::piElementData_->CreateFactory(
		DEFAULT_ELEMENT_DATA_LENGTH);
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void COutput::ProcessElement()
{
	IDataConnector* piDataConnector = QueryTool<COutput, IDataConnector>::
		QueryInterface(this, IID_IDataConnector);

	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

	CConnection* pConnection = NULL;

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections;)
	{
		pConnection = piConnectionsEnum->GetSelected();
		break;
	}
	piConnectionsEnum->Release();

	if (pConnection)
		CCmnDataFlow::piElementData_->SetItemData(0, 
			pConnection->data_.GetItemData(0));
	else 
		CCmnDataFlow::piElementData_->SetItemData(0, 0.0f);

	piConnectionsFactory->Release();

	piDataConnector->Release();
}

// IDataConnector implementations section

// IStorageController implementations section
result COutput::Serialize(FILEDev& fileDev, bool loading)
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
ulong COutput::AddRef()
{
	return ++numRef_;						
}

ulong COutput::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String COutput::GetClassString() const
{
	return _T("COutput");
}

result COutput::QueryInterface(REFIID iid, void** ppObject)
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
