#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Common/BasicDevice.h"

#include "Charts/Charts.h"

#include "Common/BasicLocator.h"

#include "Common/BasicRenderer.h"

#include "FunctionRenderer.h"

namespace Simple2dCharting
{

	FunctionRenderer::FunctionRenderer()
		: BasicRenderer()
		, color_(BasicDevice::White)
		, thickness_(1.0f)
	{
	}

	FunctionRenderer::FunctionRenderer(Color color, float thickness)
		: BasicRenderer()
		, color_(color)
		, thickness_(thickness)
	{
	}

	FunctionRenderer::~FunctionRenderer()
	{
	}

	// Public interface
	result FunctionRenderer::Render(BasicChartRef chart, BasicLocatorRef locator) const
	{
		FloatPointChart* pChart =
			dynamic_cast< FloatPointChart* >(chart.GetPointer());

		FloatPointChart::ChartLockerPtr_ locker1 = pChart->GetLocker();

		FloatPoint prev(
			std::numeric_limits<float>::infinity());

		FloatPointChart::Container_::const_iterator iter = pChart->GetContainer().begin();
		FloatPointChart::Container_::const_iterator end = pChart->GetContainer().end();

		for ( ; iter != end ; ++iter )
		{
			FloatPoint cur;

			locator->LocatePoint((*iter).x_, (*iter).y_, cur.x_, cur.y_);

			BasicRenderer::device_->DrawLine(
				color_, 
				prev.x_, prev.y_, cur.x_, cur.y_,
				thickness_);

			prev = cur;
		}

		return OK;
	}

} // Simple2dCharting
