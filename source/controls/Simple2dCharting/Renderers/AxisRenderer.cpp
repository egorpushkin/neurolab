#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Common/BasicDevice.h"

#include "Charts/Charts.h"

#include "Common/BasicLocator.h"

#include "Common/BasicRenderer.h"

#include "Common/BasicFunctor.h"

#include "AxisRenderer.h"

namespace Simple2dCharting
{

	// Parameters
	AxisRenderer::Parameters::Parameters()
		: BasicFunctor::BasicParameters()
		, axiscolor_(BasicDevice::Black)
		, rangeX_(1.0f)
		, rangeY_(1.0f)
	{
	}
	
	AxisRenderer::Parameters::~Parameters()
	{
	}

	AxisRenderer::Parameters* AxisRenderer::Parameters::Clone() const
	{
		return new Parameters(*this);
	}

	// AxisRenderer
	AxisRenderer::AxisRenderer()
		: BasicRenderer()
		, BasicFunctor()
	{
		Parameters params;
		BasicFunctor::SetParameters(params);
	}

	AxisRenderer::~AxisRenderer()
	{
	}

	// Overrides
	const AxisRenderer::Parameters& AxisRenderer::GetParameters() const
	{
		const AxisRenderer::Parameters* pParams =
			dynamic_cast< const AxisRenderer::Parameters* >(&BasicFunctor::GetParameters());
		
		if( !pParams ) 
		{
			throw std::exception("Invalid parameters operation.");
		}
		
		return *pParams;
	}

	// Public interface
	result AxisRenderer::Render(BasicChartRef /* chart */, BasicLocatorRef locator) const
	{
		FloatPoint vcentre(0.0f, 0.0f);
		FloatPoint centre;
		
		locator->LocatePoint(vcentre.x_, vcentre.y_, centre.x_, centre.y_);

		FloatPoint lefttop(0.0f, 0.0f);
		FloatPoint rightbottom(locator->GetCartesians()->GetWidth() - 1, locator->GetCartesians()->GetHeight() - 1);

		FloatPoint vlefttop;
		FloatPoint vrightbottom;

		locator->ReversePoint(lefttop.x_, lefttop.y_, vlefttop.x_, vlefttop.y_);
		locator->ReversePoint(rightbottom.x_, rightbottom.y_, vrightbottom.x_, vrightbottom.y_);

        float leftX = ceil( vlefttop.x_ / GetParameters().rangeX_ );       
		float rightX = floor( vrightbottom.x_ / GetParameters().rangeX_ );       
		
		for ( float i = leftX ; i <= rightX ; ++i )
		{		
			FloatPoint line;
            locator->LocatePoint(i * GetParameters().rangeX_, 0, line.x_, line.y_);

			BasicRenderer::device_->DrawLine(
				BasicDevice::Gray, 
				line.x_, 0, line.x_, locator->GetCartesians()->GetHeight() - 1);
		
			//if ( i == 0.0f )
			//	continue;

			char buffer[10];
			sprintf(buffer, "%0.2f", i * GetParameters().rangeX_);

			BasicRenderer::device_->DrawString(
				BasicDevice::Gray, "Times New Roman", 10, FontStyleRegular, 
				//line.x_ + 3, 0, buffer);
				line.x_ + 3, locator->GetCartesians()->GetHeight() - 13, buffer);
		}
		
		float topY = floor( vlefttop.y_ / GetParameters().rangeY_ );       
		float bottomY = ceil( vrightbottom.y_ / GetParameters().rangeY_ );       

		for ( float i = bottomY ; i <= topY ; ++i )
		{		
			FloatPoint line;
			locator->LocatePoint(0, i * GetParameters().rangeY_, line.x_, line.y_);

			BasicRenderer::device_->DrawLine(
				BasicDevice::Gray, 
				0, line.y_, locator->GetCartesians()->GetWidth() - 1, line.y_);

			//if ( i == 0.0f )
			//	continue;

			char buffer[10];
			sprintf(buffer, "%0.2f", i * GetParameters().rangeY_);

			BasicRenderer::device_->DrawString(
				BasicDevice::Gray, "Times New Roman", 10, FontStyleRegular, 
				1, line.y_, buffer);
		}

		if ( centre.x_ >= 0 && centre.x_ < locator->GetCartesians()->GetWidth() )
		{
			BasicRenderer::device_->DrawLine(
				GetParameters().axiscolor_, 
				centre.x_, 0, centre.x_, locator->GetCartesians()->GetHeight() - 1, 2.0f);
			BasicRenderer::device_->DrawLine(
				GetParameters().axiscolor_, 
				centre.x_, 0, centre.x_ - 4, 13, 2.0f);
			BasicRenderer::device_->DrawLine(
				GetParameters().axiscolor_, 
				centre.x_, 0, centre.x_ + 4, 13, 2.0f);

			BasicRenderer::device_->DrawString(
				GetParameters().axiscolor_, "Times New Roman", 18, FontStyleBold, 
				centre.x_ - 21, 0, "Y");
		}

		if ( centre.y_ >= 0 && centre.y_ < locator->GetCartesians()->GetHeight() )
		{
			BasicRenderer::device_->DrawLine(
				GetParameters().axiscolor_, 
				0, centre.y_, locator->GetCartesians()->GetWidth() - 1, centre.y_, 2.0f);
			BasicRenderer::device_->DrawLine(
				GetParameters().axiscolor_, 
				locator->GetCartesians()->GetWidth() - 1, centre.y_, 
				locator->GetCartesians()->GetWidth() - 1 - 13, centre.y_ - 4, 2.0f);
			BasicRenderer::device_->DrawLine(
				GetParameters().axiscolor_, 
				locator->GetCartesians()->GetWidth() - 1, centre.y_, 
				locator->GetCartesians()->GetWidth() - 1 - 13, centre.y_ + 4, 2.0f);

			BasicRenderer::device_->DrawString(
				GetParameters().axiscolor_, "Times New Roman", 18, FontStyleBold, 
				locator->GetCartesians()->GetWidth() - 20, centre.y_ - 23, "X");
		}

		return OK;
	}

} // Simple2dCharting
