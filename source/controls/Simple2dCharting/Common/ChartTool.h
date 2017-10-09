#ifndef CHARTTOOL_H__S2DCHARTING__INCLUDED_
#define CHARTTOOL_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class ChartTool
	{
	public:

		ChartTool();
		ChartTool(BasicChartRef chart, BasicRendererRef renderer, BasicLocatorRef locator, const std::string name = "");
		virtual ~ChartTool();

		// Public interface
		virtual void SetChart(BasicChartRef chart);
		virtual BasicChartPtr GetChart() const;

		virtual void SetRenderer(BasicRendererRef renderer);
		virtual BasicRendererPtr GetRenderer() const;

		virtual void SetLocator(BasicLocatorRef locator);
		virtual BasicLocatorPtr GetLocator() const;

		virtual void SetName(const std::string& name);
		virtual std::string GetName() const;

	protected:

		BasicChartPtr chart_;
		BasicRendererPtr renderer_;
		BasicLocatorPtr locator_;

		std::string name_;

	}; // ChartTool

	typedef Loki::StrongPtr< ChartTool > ChartToolPtr;
	typedef const ChartToolPtr& ChartToolRef;

} // Simple2dCharting

#endif // !CHARTTOOL_H__S2DCHARTING__INCLUDED_
