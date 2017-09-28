#ifndef BASICRENDERER_H__S2DCHARTING__INCLUDED_
#define BASICRENDERER_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BasicRenderer
	{
	public:

		BasicRenderer();
		virtual ~BasicRenderer();

		// Public interface
		virtual void SetDevice(BasicDeviceRef device);
	
		// Pure interface
		virtual result Render(BasicChartRef chart, BasicLocatorRef locator) const = 0;

	protected:

		BasicDevicePtr device_;



	}; // BasicRenderer

	typedef Loki::StrongPtr< BasicRenderer > BasicRendererPtr;
	typedef const BasicRendererPtr& BasicRendererRef;

} // Simple2dCharting

#endif // !BASICRENDERER_H__S2DCHARTING__INCLUDED_
