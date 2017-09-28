#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Charts/Charts.h"

#include "Common/BasicLocator.h"

#include "AutomaticLocator.h"

#include "Geometry/Basics.h"

namespace Simple2dCharting
{

	AutomaticLocator::AutomaticLocator()
		: BasicLocator()
		, border_(0.0f)
	{
	}

	AutomaticLocator::AutomaticLocator(CartesianCoordinatesRef cartesians)
		: BasicLocator(cartesians)
		, border_(0.0f)
	{
	}
	
	AutomaticLocator::~AutomaticLocator()
	{
	}

	// Public interface
	// Locating points
	void AutomaticLocator::LocatePoint(float x, float y, float& xr, float& yr) const
	{
		GeometryBasics::TransformPoint(
			x, y, 
			BasicLocator::cartesians_->GetX(), BasicLocator::cartesians_->GetY(),
			BasicLocator::cartesians_->GetScaleX(), BasicLocator::cartesians_->GetScaleY(),
			xr, yr
		);
	}

	void AutomaticLocator::UpdateCartesians(BasicChartRef chart) const
	{
		FloatPointChart* pChart =
			dynamic_cast< FloatPointChart* >(chart.GetPointer());

		FloatPointChart::ChartLockerPtr_ locker1 = pChart->GetLocker();

		if ( pChart->GetContainer().size() == 0 )
			return;

		FloatPoint back = pChart->GetContainer().back();

		LocatePoint(back.x_, back.y_, back.x_, back.y_);

		if ( back.x_ < 0 )
		{
			BasicLocator::cartesians_->SetX(
				BasicLocator::cartesians_->GetX() + (-1.0f * back.x_ + border_)
			);
		}

		if ( back.x_ >= BasicLocator::cartesians_->GetWidth() )
		{
			BasicLocator::cartesians_->SetX(
				BasicLocator::cartesians_->GetX() - (back.x_ - BasicLocator::cartesians_->GetWidth() + border_)
			);
		}

		if ( back.y_ < 0 )
		{
			BasicLocator::cartesians_->SetY(
				BasicLocator::cartesians_->GetY() + (-1.0f * back.y_ + border_)
			);
		}

		if ( back.y_ >= BasicLocator::cartesians_->GetHeight() )
		{
			BasicLocator::cartesians_->SetY(
				BasicLocator::cartesians_->GetY() - (back.y_ - BasicLocator::cartesians_->GetHeight() + border_)
			);
		}

	}

} // Simple2dCharting
