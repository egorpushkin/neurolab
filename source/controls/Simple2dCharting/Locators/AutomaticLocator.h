#ifndef AUTOMATICLOCATOR_H__S2DCHARTING__INCLUDED_
#define AUTOMATICLOCATOR_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class AutomaticLocator : public BasicLocator
	{
	public:

		AutomaticLocator();
		AutomaticLocator(CartesianCoordinatesRef cartesians);
		virtual ~AutomaticLocator();

		// Public interface
		// Locating points
		virtual void LocatePoint(float x, float y, float& xr, float& yr) const;
		virtual void UpdateCartesians(BasicChartRef chart) const;

	private:
		
		float border_;
		
	}; // AutomaticLocator

	typedef Loki::StrongPtr< AutomaticLocator > AutomaticLocatorPtr;
	typedef const AutomaticLocatorPtr& AutomaticLocatorRef;

} // Simple2dCharting

#endif // !AUTOMATICLOCATOR_H__S2DCHARTING__INCLUDED_
