#include "Includes.h"

#include "Cartesian/Cartesian.h"

#include "BasicDevice.h"

#include "BasicChart.h"

#include "BasicLocator.h"

#include "BasicRenderer.h"

#include "ChartTool.h"

namespace Simple2dCharting
{

	ChartTool::ChartTool()
		: chart_()
		, renderer_()
		, locator_()
		, name_()
	{
	}

	ChartTool::ChartTool(BasicChartRef chart, BasicRendererRef renderer, BasicLocatorRef locator, const std::string name)
		: chart_(chart)
		, renderer_(renderer)
		, locator_(locator)
		, name_(name)
	{
	}

	ChartTool::~ChartTool()
	{
	}

	// Public interface
	void ChartTool::SetChart(BasicChartRef chart)
	{
		chart_ = chart;
	}

	BasicChartPtr ChartTool::GetChart() const 
	{
		return chart_;
	}

	void ChartTool::SetRenderer(BasicRendererRef renderer)
	{
		renderer_ = renderer;
	}

	BasicRendererPtr ChartTool::GetRenderer() const 
	{
		return renderer_;
	}

	void ChartTool::SetLocator(BasicLocatorRef locator)
	{
		locator_ = locator;
	}

	BasicLocatorPtr ChartTool::GetLocator() const 
	{
		return locator_;
	}

	void ChartTool::SetName(const std::string& name)
	{
		name_ = name;
	}

	std::string ChartTool::GetName() const 
	{
		return name_;
	}

} // Simple2dCharting
