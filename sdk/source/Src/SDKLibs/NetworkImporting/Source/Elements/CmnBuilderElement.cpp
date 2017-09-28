#include "../../Headers/CmnNetworkImportingLib.h"
#include "BuilderElements/Common/Common.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;
using namespace ExternalOutputEngine;

CCmnBuilderElement::CCmnBuilderElement()
	: piBuilderControl_(NULL)
	, pntPosition_()
	, selected_(false)
	, menuResourceId_(WRONG_ELEMENT_RESOURCE_ID)
	, subMenuResourceId_(WRONG_ELEMENT_RESOURCE_ID)
	, layerBehaviour_(true)
	, elementTextureActive_(_T(""))
	, elementTexturePassive_(_T(""))
	, imageWidth_(SIZE_LAYER_IMAGE_WIDTH)
	, imageHeight_(SIZE_LAYER_IMAGE_HEIGHT)
	, shortNameOffset_(0)
	, nameOffset_(0)
{
}

CCmnBuilderElement::~CCmnBuilderElement()
{
	if (piBuilderControl_)
		piBuilderControl_->Release();
}

// Custom render tools
result CCmnBuilderElement::RenderLayer() const
{
#ifdef USING_INTERNAL_OUTPUT_ENGINE_STUB	
	return S_OK;
#else
	// Universal render code
	// Warning. NOT IMPLEMENTED.
#endif // USING_INTERNAL_OUTPUT_ENGINE_STUB	
}

// IStorageController implementations section
result CCmnBuilderElement::Serialize(FILEDev& fileDev, bool loading)
{
	if (loading)
	{
		fileDev.Read(&pntPosition_.x, sizeof(uint));
		fileDev.Read(&pntPosition_.y, sizeof(uint));
	} else
	{
		fileDev.Write(&pntPosition_.x, sizeof(uint));
		fileDev.Write(&pntPosition_.y, sizeof(uint));
	}

	return S_OK;
}

// IBuilderElement implementations section
void CCmnBuilderElement::SetOutputControl(IBuilderControl* piControl)
{
	piBuilderControl_ = piControl;

	if (piBuilderControl_)
		piBuilderControl_->AddRef();
}

IBuilderControl* CCmnBuilderElement::GetOutputControl() const
{	
	piBuilderControl_->AddRef();

	return piBuilderControl_;
}

void CCmnBuilderElement::SetElementPosition(const BuilderPoint& point)
{
	pntPosition_ = point;
}

const BuilderPoint& CCmnBuilderElement::GetElementPosition()
{
	return pntPosition_;
}

void CCmnBuilderElement::RenderElement() const
{
	if (layerBehaviour_)
		RenderLayer();
}

bool CCmnBuilderElement::IsClicked(const BuilderPoint& /* point */) const
{
#ifdef USING_INTERNAL_OUTPUT_ENGINE_STUB	
	return false;
#else
	// Universal code for click detection	
	// Warning. NOT IMPLEMENTED.

	return false;
#endif // USING_INTERNAL_OUTPUT_ENGINE_STUB	
}

void CCmnBuilderElement::SelectElement(bool select)
{
	selected_ = select;
}

bool CCmnBuilderElement::IsSelected() const
{
	return selected_;
}

void CCmnBuilderElement::TrackPopupMenu(const BuilderPoint& /* point */) const
{
#ifdef USING_INTERNAL_OUTPUT_ENGINE_STUB	
#else
	// Universal code for tracking popup menu
	// Warning. NOT IMPLEMENTED.
#endif // USING_INTERNAL_OUTPUT_ENGINE_STUB	
}

const BuilderPoint& CCmnBuilderElement::GetPositionForConnectedElement(const CConnection* /* pConnection */)
{
	return GetElementPosition();
}
