#include "Neuron.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CNeuron::CNeuron(void)
	// Base class constructors invocation
	: CCmnElement()
	, CCmnBuilderElement()
	, CCmnDataFlow()
	, CCmnDataConnector()
	// ICommon  data fields initialization
	, numRef_(0)
{	
	// IElement data fields initialization (declared in CCmnElement wrapper)
	elementType_ = ET_PROCESSOR;
	sysName_ = "Neuron";
	sysTitle_ = "Neuron";
	sysShortName_ = "N";
	// IBuilderElement data fields initialization (declared in CCmnBuilderElement wrapper)
	menuResourceId_ = IDR_ELEMENTS_POPUPS;
	subMenuResourceId_ = IDR_EP_NEURON_MENU_ITEM;
	layerBehaviour_ = false;
	elementTextureActive_ = _T("Neuron_Active");
	elementTexturePassive_ = _T("Neuron_Passive");
	imageWidth_ = SIZE_NEURON_IMAGE_DIAMETER;
	imageHeight_ = SIZE_NEURON_IMAGE_DIAMETER;
	shortNameOffset_ = 8;
	nameOffset_ = 0;
	// IDataFlow data fields initialization (declared in CCmnDataFlow wrapper)
	// IDataConnector data fields initialization (declared in CCmnDataConnector wrapper)
	// ILayerControl data fields initialization (declared in CCmnLayerControl wrapper)
}

CNeuron::~CNeuron(void)
{
}

// Custom tools
void CNeuron::PostInitialize()
{
	CCmnDataFlow::piElementData_->CreateFactory(
		DEFAULT_ELEMENT_DATA_LENGTH);
}

// IElement implementations section

// IBuilderElement implementations section

// IDataFlow implementations section
void CNeuron::ProcessElement()
{
	IDataConnector* piDataConnector = QueryTool<CNeuron, IDataConnector>::
		QueryInterface(this, IID_IDataConnector);
	
	IConnectionsFactory* piConnectionsFactory = piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

	float preparedOutput = 0.0f;

	IConnectionsEnumerator* piConnectionsEnum = piConnectionsFactory->GetConnectionsEnumerator();
	for(bool hasConnections = piConnectionsEnum->SelectFirst(); hasConnections; hasConnections = piConnectionsEnum->SelectNext())
	{
		CConnection* pConnection = piConnectionsEnum->GetSelected();

		for (uint i = 0;i < pConnection->data_.GetDataLength();i++)
			preparedOutput += pConnection->data_.GetItemData(i) * 
				pConnection->weights_.GetItemData(i);
	}
	piConnectionsEnum->Release();

	if (CCmnDataFlow::pActivateFunction_)
		preparedOutput = (*CCmnDataFlow::pActivateFunction_->pProcesTransferFunction_)
			(
				CCmnDataFlow::pActivateFunction_, preparedOutput
			);

	CCmnDataFlow::piElementData_->SetItemData(0, preparedOutput);

	piConnectionsFactory->Release();

	piDataConnector->Release();
}

// IDataConnector implementations section

// IStorageController implementations section
result CNeuron::Serialize(FILEDev& fileDev, bool loading)
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
ulong CNeuron::AddRef()
{
	return ++numRef_;						
}

ulong CNeuron::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CNeuron::GetClassString() const
{
	return _T("CNeuron");
}

result CNeuron::QueryInterface(REFIID iid, void** ppObject)
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
