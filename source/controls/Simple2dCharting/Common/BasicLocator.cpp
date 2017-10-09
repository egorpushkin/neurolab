#include "Includes.h"

#include "Cartesian/Cartesian.h"

#include "BasicChart.h"

#include "BasicLocator.h"

namespace Simple2dCharting
{

	BasicLocator::BasicLocator()
		: cartesians_()
	{
	}

	BasicLocator::BasicLocator(CartesianCoordinatesRef cartesians)
		: cartesians_(cartesians)
	{
	}

	BasicLocator::~BasicLocator()
	{
	}

	// Initialization interface
	void BasicLocator::SetCartesians(CartesianCoordinatesRef cartesians)
	{
		cartesians_ = cartesians;
	}

	CartesianCoordinatesPtr BasicLocator::GetCartesians()
	{
		return cartesians_;
	}

	// Public interface
	// Locating points
	void BasicLocator::UpdateCartesians(BasicChartRef /* chart */) const
	{
	}

	void BasicLocator::LocatePoint(float /* vx */, float /* vy */, float& /* x */, float& /* y */) const
	{
	}

	void BasicLocator::ReversePoint(float /* x */, float /* y */, float& /* vx */, float& /* vy */) const
	{
	}

	// Locating viewport
	void BasicLocator::ZoomIn()
	{
	}

	void BasicLocator::ZoomOut()
	{
	}

	void BasicLocator::MoveViewport(float /* dx */, float /* dy */)
	{
	}

} // Simple2dCharting
