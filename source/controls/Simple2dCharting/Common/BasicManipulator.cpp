#include "Includes.h"

#include "Cartesian/Cartesian.h"

#include "BasicChart.h"

#include "BasicLocator.h"

#include "BasicManipulator.h"

namespace Simple2dCharting
{

	BasicManipulator::BasicManipulator()
		: locator_()
	{
	}
	
	BasicManipulator::BasicManipulator(BasicLocatorRef locator)
		: locator_(locator)
	{
	}

	BasicManipulator::~BasicManipulator()
	{
	}

	// Initialization interface
	void BasicManipulator::SetLocator(BasicLocatorRef locator)
	{
		locator_ = locator;
	}

	// Public interface
	void BasicManipulator::ZoomIn()
	{	
		locator_->ZoomIn();
	}

	void BasicManipulator::ZoomOut()
	{
		locator_->ZoomOut();
	}

	void BasicManipulator::MoveViewport(float dx, float dy)
	{
		locator_->MoveViewport(dx, dy);
	}

} // Simple2dCharting
