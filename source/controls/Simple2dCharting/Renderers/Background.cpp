#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Common/BasicDevice.h"

#include "Charts/Charts.h"

#include "Common/BasicLocator.h"

#include "Common/BasicRenderer.h"

#include "Background.h"

namespace Simple2dCharting
{

	BackgroundRenderer::BackgroundRenderer()
		: BasicRenderer()
		, bgcolor_(BasicDevice::Aqua)
	{
	}

	BackgroundRenderer::BackgroundRenderer(Color color)
		: BasicRenderer()
		, bgcolor_(color)
	{
	}

	BackgroundRenderer::~BackgroundRenderer()
	{
	}

	// Public interface
	result BackgroundRenderer::Render(BasicChartRef /* chart */, BasicLocatorRef locator) const
	{
		BasicRenderer::device_->FillRectangle(
			bgcolor_, 
			0.0f, 0.0f, 
			(float) locator->GetCartesians()->GetWidth(), 
			(float) locator->GetCartesians()->GetHeight()
		);

		return OK;
	}

} // Simple2dCharting
