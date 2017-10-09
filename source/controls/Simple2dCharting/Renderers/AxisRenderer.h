#ifndef AXISRENDERER_H__S2DCHARTING__INCLUDED_
#define AXISRENDERER_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class AxisRenderer 
		: public BasicRenderer
		, public BasicFunctor
	{
	public:

		class Parameters : public BasicFunctor::BasicParameters
		{
		public:

			Parameters();		
			virtual ~Parameters();

			// Public interface
			virtual Parameters* Clone() const;

			Color axiscolor_;
			float rangeX_;
			float rangeY_;

		};

		AxisRenderer();
		virtual ~AxisRenderer();

		// Overrides
		virtual const Parameters& GetParameters() const;
	
		// Public interface
		virtual result Render(BasicChartRef chart, BasicLocatorRef locator) const;

	}; // BackgroundRenderer

	typedef Loki::StrongPtr< AxisRenderer > AxisRendererPtr;
	typedef const AxisRendererPtr& AxisRendererRef;

} // Simple2dCharting

#endif // !AXISRENDERER_H__S2DCHARTING__INCLUDED_
