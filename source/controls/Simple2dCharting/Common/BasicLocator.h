#ifndef BASICLOCATOR_H__S2DCHARTING__INCLUDED_
#define BASICLOCATOR_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BasicLocator
	{
	public:

		BasicLocator();
		BasicLocator(CartesianCoordinatesRef cartesians);
		virtual ~BasicLocator();

		// Initialization interface
		virtual void SetCartesians(CartesianCoordinatesRef cartesians);
		virtual CartesianCoordinatesPtr GetCartesians();

		// Public interface
		// Locating points
		virtual void UpdateCartesians(BasicChartRef chart) const;
		virtual void LocatePoint(float vx, float vy, float& x, float& y) const;
		virtual void ReversePoint(float x, float y, float& vx, float& vy) const;

		// Locating viewport
		virtual void ZoomIn();
		virtual void ZoomOut();

		virtual void MoveViewport(float dx, float dy);

	protected:

		CartesianCoordinatesWeak cartesians_;

        
	}; // BasicLocator

	typedef Loki::StrongPtr< BasicLocator > BasicLocatorPtr;
	typedef Loki::StrongPtr< BasicLocator, false > BasicLocatorWeak;
	typedef const BasicLocatorPtr& BasicLocatorRef;

} // Simple2dCharting

#endif // !BASICLOCATOR_H__S2DCHARTING__INCLUDED_
