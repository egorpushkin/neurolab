#ifndef WHOLELOCATOR_H__S2DCHARTING__INCLUDED_
#define WHOLELOCATOR_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class WholeLocator : public BasicLocator
	{
	public:

		WholeLocator();
		WholeLocator(CartesianCoordinatesRef cartesians);
		virtual ~WholeLocator();

		// Public interface
		// Locating points
		virtual void LocatePoint(float x, float y, float& xr, float& yr) const;
		virtual void UpdateCartesians(BasicChartRef chart) const;

	protected:

		float border_;
		
	}; // AutomaticLocator

	typedef Loki::StrongPtr< WholeLocator > WholeLocatorPtr;
	typedef const WholeLocatorPtr& WholeLocatorRef;

} // Simple2dCharting

#endif // !WHOLELOCATOR_H__S2DCHARTING__INCLUDED_
