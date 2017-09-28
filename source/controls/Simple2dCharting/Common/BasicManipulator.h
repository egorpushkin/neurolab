#ifndef BASICMANIPULATOR_H__S2DCHARTING__INCLUDED_
#define BASICMANIPULATOR_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BasicManipulator
	{
	public:

		BasicManipulator();
		BasicManipulator(BasicLocatorRef locator);
		virtual ~BasicManipulator();

		// Initialization interface
		virtual void SetLocator(BasicLocatorRef locator);

		// Public interface
		virtual void ZoomIn();
		virtual void ZoomOut();

		virtual void MoveViewport(float dx, float dy);

	private:

		BasicLocatorWeak locator_;


	}; // BasicManipulator

	typedef Loki::StrongPtr< BasicManipulator > BasicManipulatorPtr;
	typedef const BasicManipulatorPtr& BasicManipulatorRef;

} // Simple2dCharting

#endif // !BASICMANIPULATOR_H__S2DCHARTING__INCLUDED_
