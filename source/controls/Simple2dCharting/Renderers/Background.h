#ifndef BACKGROUND_H__S2DCHARTING__INCLUDED_
#define BACKGROUND_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BackgroundRenderer : public BasicRenderer
	{
	public:

		BackgroundRenderer();
		BackgroundRenderer(Color color);
		virtual ~BackgroundRenderer();
	
		// Public interface
		virtual result Render(BasicChartRef chart, BasicLocatorRef locator) const;

	protected:

		Color bgcolor_;

	}; // BackgroundRenderer

} // Simple2dCharting

#endif // !BACKGROUND_H__S2DCHARTING__INCLUDED_
