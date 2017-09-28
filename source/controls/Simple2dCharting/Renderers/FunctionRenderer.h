#ifndef FUNCTIONRENDERER_H__S2DCHARTING__INCLUDED_
#define FUNCTIONRENDERER_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class FunctionRenderer : public BasicRenderer
	{
	public:

		FunctionRenderer();
		FunctionRenderer(Color color, float thickness = 1.0f);
		virtual ~FunctionRenderer();
	
		// Public interface
		virtual result Render(BasicChartRef chart, BasicLocatorRef locator) const;

	protected:

		Color color_;
		float thickness_;

	}; // FunctionRenderer

} // Simple2dCharting

#endif // !FUNCTIONRENDERER_H__S2DCHARTING__INCLUDED_
