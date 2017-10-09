#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Charts/Charts.h"

#include "Common/BasicLocator.h"

#include "WholeLocator.h"

#undef min
#undef max

namespace Simple2dCharting
{

	WholeLocator::WholeLocator()
		: BasicLocator()
		, border_(5.0f)
	{
	}

	WholeLocator::WholeLocator(CartesianCoordinatesRef cartesians)
		: BasicLocator(cartesians)
		, border_(5.0f)
	{
	}
	
	WholeLocator::~WholeLocator()
	{
	}

	// Public interface
	// Locating points
	void WholeLocator::LocatePoint(float x, float y, float& xr, float& yr) const
	{
		xr = 		
			BasicLocator::cartesians_->GetX() + 
			x * BasicLocator::cartesians_->GetScaleX();

		yr = 
			BasicLocator::cartesians_->GetY() - 
			y * BasicLocator::cartesians_->GetScaleY();
	}

	void WholeLocator::UpdateCartesians(BasicChartRef chart) const
	{
		FloatPointChart* pChart =
			dynamic_cast< FloatPointChart* >(chart.GetPointer());

		FloatPointChart::ChartLockerPtr_ locker1 = pChart->GetLocker();

		FloatPoint left(std::numeric_limits< float >::max());
		FloatPoint right(std::numeric_limits< float >::min());
		FloatPoint top(std::numeric_limits< float >::min());
		FloatPoint bottom(std::numeric_limits< float >::max());

		if ( pChart->GetContainer().size() == 0 )
			return;

		FloatPointChart::Container_::const_iterator iter = pChart->GetContainer().begin();
		FloatPointChart::Container_::const_iterator end = pChart->GetContainer().end();

		for ( ; iter != end ; ++iter )
		{
			if ( (*iter).x_ < left.x_ )
				left = (*iter);

			if ( (*iter).x_ > right.x_ )
				right = (*iter);

			if ( (*iter).y_ < bottom.y_ )
				bottom = (*iter);

			if ( (*iter).y_ > top.y_ )
				top = (*iter);
		}

		FloatPoint vcentre(left.x_ + (right.x_ - left.x_)/2, bottom.y_ + (top.y_ - bottom.y_)/2);
		FloatPoint rect(right.x_ - left.x_, top.y_ - bottom.y_);

		FloatPoint scale(
			(BasicLocator::cartesians_->GetWidth() - border_ * 2) / rect.x_,
			(BasicLocator::cartesians_->GetHeight() - border_ * 2) / rect.y_);

		FloatPoint centre(
			BasicLocator::cartesians_->GetWidth() / 2 - vcentre.x_ * scale.x_, 
			BasicLocator::cartesians_->GetHeight() / 2 + vcentre.y_ * scale.y_);

		BasicLocator::cartesians_->SetX(centre.x_);
		BasicLocator::cartesians_->SetY(centre.y_);
		
		BasicLocator::cartesians_->SetScaleX(scale.x_);
		BasicLocator::cartesians_->SetScaleY(scale.y_);
        
	}

} // Simple2dCharting
