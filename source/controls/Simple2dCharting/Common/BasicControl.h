#ifndef BASICCONTROL_H__S2DCHARTING__INCLUDED_
#define BASICCONTROL_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BasicControl
	{
	public:

		typedef std::vector< ChartToolPtr > ChartsContainer_;
		typedef ChartsContainer_::iterator ChartsIter_;
		typedef ChartsContainer_::const_iterator ChartsCIter_;

		BasicControl();
		BasicControl(BasicDeviceRef device);
		virtual ~BasicControl();

		// Public interface
		virtual void SetGlobalLocator(BasicLocatorRef locator);
		virtual void SetGlobalManipulator(BasicManipulatorRef manipulator);

		virtual CartesianCoordinatesPtr GetCartesians();

		virtual void AddChart(BasicChartRef chart, BasicRendererRef renderer, BasicLocatorRef locator, const std::string name = "");
		virtual void AddChart(ChartToolRef chartTool);
		virtual ChartToolPtr GetChart(const std::string name);


	protected:
		
		virtual void RenderCharts();




	protected:
		
		CartesianCoordinatesPtr cartesians_;
		BasicDevicePtr device_;
		BasicLocatorPtr locator_;
		BasicManipulatorPtr manipulator_;
		
		ChartsContainer_ charts_;
        
		
		
	}; // BasicLocator

	typedef Loki::StrongPtr< BasicControl > BasicControlPtr;
	typedef const BasicControlPtr& BasicControlRef;

} // Simple2dCharting

#endif // !BASICCONTROL_H__S2DCHARTING__INCLUDED_
