#include "../../Headers/CmnNetworkImportingLib.h"
#include "BuilderElements/Common/Common.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;
using namespace ExternalOutputEngine;

#define MAX_TITLE_LENGTH				256

CCmnElement::CCmnElement()
	: elementId_(WRONG_ELEMENT_ID)
	, sysName_("")
	, sysTitle_("")
	, sysShortName_("")
	, elementType_(ET_PROCESSOR)
{
}

CCmnElement::~CCmnElement()
{
}

// Custom operations
result CCmnElement::RemoveElement()
{
	// Updating builder control state
	IBuilderElement* piBuilderElement = QueryTool<IElement, IBuilderElement>::
		QueryInterface((IElement*)this, IID_IBuilderElement);

	IBuilderControl* piBuilderControl = piBuilderElement->GetOutputControl();
	if (piBuilderControl)
	{
		piBuilderControl->SetActiveElement(NULL);			
		piBuilderControl->Release();
	}
	
	piBuilderElement->Release();

	// Releasing element
	((IElement*)this)->Release();

	return S_OK;
}

result CCmnElement::SetAddConnectionState(uint state)
{
	assert((state == DC_INPUTS_FACTORY) || (state == DC_OUTPUTS_FACTORY));

	// Updating builder control state
	IBuilderElement* piBuilderElement = QueryTool<IElement, IBuilderElement>::
		QueryInterface((IElement*)this, IID_IBuilderElement);

	IBuilderControl* piBuilderControl = piBuilderElement->GetOutputControl();
	if (piBuilderControl)
	{
		piBuilderControl->SetBuilderState(BS_CONNECTING);	
		piBuilderControl->Release();
	}

	piBuilderElement->Release();

	// Updating element internal state
	IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
		QueryInterface((IElement*)this, IID_IDataConnector);

	piDataConnector->SetAddConnectionState(state, DEFAULT_CONNECTIONS_COUNT);

	piDataConnector->Release();

	return S_OK;
}

// IStorageController implementations section
result CCmnElement::Serialize(FILEDev& fileDev, bool loading)
{
	if (loading)
	{
		StringA tempString;

		fileDev.Read(&elementId_, sizeof(int));
		fileDev.ReadStringA(tempString);
	} else
	{
		fileDev.WriteStringA(sysName_);
		fileDev.WriteStringA(sysTitle_);

		fileDev.Write(&elementId_, sizeof(int));
		fileDev.WriteStringA(sysTitle_);
	}

	return S_OK;
}

// IElement implementations section
void CCmnElement::SetElementID(uint eleemntId)
{	
	elementId_ = eleemntId;
}

uint CCmnElement::GetElementID() const
{
	return elementId_;
}

uint CCmnElement::GetElementType() const
{
	return elementType_;
}

void CCmnElement::SetSysName(const StringA& name)
{
	sysName_ = name;
}

const StringA& CCmnElement::GetSysName() const
{
	return sysName_;
}

void CCmnElement::SetSysTitle(const StringA& title)
{
	sysTitle_ = title;
}

const StringA& CCmnElement::GetSysTitle() const
{
	return sysTitle_;
}

void CCmnElement::SetShortName(const StringA& name)
{
	sysShortName_ = name;
}

const StringA& CCmnElement::GetShortName() const
{
	return sysShortName_;
}

void CCmnElement::CommandNotify(wparam wParam, lparam /* lParam */)
{
	int commandCode = LOWORD(wParam);
	switch (commandCode)
	{
	case ID_REMOVE:
		RemoveElement();
		break;	
	case ID_ADD_DENDRITE:			
		SetAddConnectionState(DC_INPUTS_FACTORY);			
		break;
	case ID_ADD_AXON:			
		SetAddConnectionState(DC_OUTPUTS_FACTORY);			
		break;
	}
}	


