#include "Includes.h"

#include "Cartesian/Cartesian.h"

#include "BasicDevice.h"

#include "BasicChart.h"

#include "BasicLocator.h"

#include "BasicRenderer.h"

#include "BasicManipulator.h"

#include "ChartTool.h"

#include "BasicControl.h"

#include "Locators/CartesiansLocator.h"

namespace Simple2dCharting
{

	BasicControl::BasicControl()
		: cartesians_(new CartesianCoordinates)
		, device_()
		, locator_(new CartesiansLocator(cartesians_))
		, manipulator_(new BasicManipulator(locator_))
		, charts_()
	{
	}

	BasicControl::BasicControl(BasicDeviceRef device)
		: cartesians_(new CartesianCoordinates)
		, device_(device)
		, locator_(new CartesiansLocator(cartesians_))
		, manipulator_(new BasicManipulator(locator_))
		, charts_()
	{
	}

	BasicControl::~BasicControl()
	{
	}

	// Public interface
	void BasicControl::SetGlobalLocator(BasicLocatorRef locator)
	{
		locator_ = locator;
		manipulator_->SetLocator(locator_);
	}

	void BasicControl::SetGlobalManipulator(BasicManipulatorRef manipulator)
	{
		manipulator_ = manipulator;
		manipulator_->SetLocator(locator_);
	}

	CartesianCoordinatesPtr BasicControl::GetCartesians()
	{
		return cartesians_;
	}

	void BasicControl::AddChart(BasicChartRef chart, BasicRendererRef renderer, BasicLocatorRef locator, const std::string name)
	{
		AddChart(
			new ChartTool(chart, renderer, locator, name)
		);
	}

	void BasicControl::AddChart(ChartToolRef chartTool)
	{
		chartTool->GetLocator()->SetCartesians(cartesians_);
		chartTool->GetRenderer()->SetDevice(device_);

		charts_.push_back(chartTool);
	}

	ChartToolPtr BasicControl::GetChart(const std::string name)
	{
		ChartsCIter_ iter = charts_.begin();
		ChartsCIter_ end = charts_.end();

		for ( ; iter != end ; ++iter )
		{
			if ( (*iter)->GetName() == name )
                return (*iter);
		}

		return NULL;
	}

	void BasicControl::RenderCharts()
	{
		ChartsCIter_ iter = charts_.begin();
		ChartsCIter_ end = charts_.end();

		for ( ; iter != end ; ++iter )
		{
			ChartToolPtr chartTool = (*iter);

			// Update cartesians
			chartTool->GetLocator()->UpdateCartesians(
				chartTool->GetChart()	
			);
		}	

		iter = charts_.begin();
		end = charts_.end();

		for ( ; iter != end ; ++iter )
		{
			ChartToolPtr chartTool = (*iter);

            // Render chart
            chartTool->GetRenderer()->Render(
				chartTool->GetChart(),
				chartTool->GetLocator()
			);
		}
	}

} // Simple2dCharting
