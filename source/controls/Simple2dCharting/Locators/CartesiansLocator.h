#ifndef CARTESIANSLOCATOR_H__S2DCHARTING__INCLUDED_
#define CARTESIANSLOCATOR_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class CartesiansLocator : public BasicLocator
	{
	public:

		CartesiansLocator();
		CartesiansLocator(CartesianCoordinatesRef cartesians);
		virtual ~CartesiansLocator();

		// Public interface
		// Locating points
		virtual void LocatePoint(float vx, float vy, float& x, float& y) const;
		virtual void ReversePoint(float x, float y, float& vx, float& vy) const;

		// Locating viewport
		virtual void ZoomIn();
		virtual void ZoomOut();

		virtual void MoveViewport(float dx, float dy);

	protected:

		virtual void Zoom(float ratio);

	}; // CartesiansLocator

	typedef Loki::StrongPtr< CartesiansLocator > CartesiansLocatorPtr;
	typedef const CartesiansLocatorPtr& CartesiansLocatorRef;

} // Simple2dCharting

#endif // !CARTESIANSLOCATOR_H__S2DCHARTING__INCLUDED_
