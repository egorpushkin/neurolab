#ifndef BASICCHART_H__S2DCHARTING__INCLUDED_
#define BASICCHART_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BasicChart;

	typedef Loki::StrongPtr< BasicChart > BasicChartPtr;
	typedef const BasicChartPtr& BasicChartRef;

	class BasicChart
	{
	public:

		BasicChart();
		virtual ~BasicChart();

		// Public interface 
		virtual BasicChartPtr Clone();

	private:

	};

} // Simple2dCharting

#endif // !BASICCHART_H__S2DCHARTING__INCLUDED_
