#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Charts/Charts.h"

#include "Common/BasicLocator.h"

#include "CartesiansLocator.h"

#include "Geometry/Basics.h"

namespace Simple2dCharting
{

	CartesiansLocator::CartesiansLocator()
		: BasicLocator()
	{
	}

	CartesiansLocator::CartesiansLocator(CartesianCoordinatesRef cartesians)
		: BasicLocator(cartesians)
	{
	}
	
	CartesiansLocator::~CartesiansLocator()
	{
	}

	// Public interface
	// Locating points
	void CartesiansLocator::LocatePoint(float vx, float vy, float& x, float& y) const
	{
		GeometryBasics::TransformPoint(
			vx, vy, 
			BasicLocator::cartesians_->GetX(), BasicLocator::cartesians_->GetY(),
			BasicLocator::cartesians_->GetScaleX(), BasicLocator::cartesians_->GetScaleY(),
			x, y
		);
	}

	void CartesiansLocator::ReversePoint(float x, float y, float& vx, float& vy) const
	{
		GeometryBasics::InverseTransform(
			x, y, 
			BasicLocator::cartesians_->GetX(), BasicLocator::cartesians_->GetY(),
			BasicLocator::cartesians_->GetScaleX(), BasicLocator::cartesians_->GetScaleY(),
			vx, vy
		);
	}

	// Locating viewport
	void CartesiansLocator::ZoomIn()
	{
		Zoom(2.0f);
	}

	void CartesiansLocator::ZoomOut()
	{
		Zoom(0.5f);
	}

	void CartesiansLocator::Zoom(float ratio)
	{
		FloatPoint centre;

		GeometryBasics::InverseTransform(
			cartesians_->GetWidth() / 2, cartesians_->GetHeight() / 2,
			BasicLocator::cartesians_->GetX(), BasicLocator::cartesians_->GetY(),
			BasicLocator::cartesians_->GetScaleX(), BasicLocator::cartesians_->GetScaleY(),
			centre.x_, centre.y_
		);

		cartesians_->SetScaleX(cartesians_->GetScaleX() * ratio);		
		cartesians_->SetScaleY(cartesians_->GetScaleY() * ratio);

		float newCentreX = cartesians_->GetWidth() / 2 - centre.x_ * cartesians_->GetScaleX();
		float newCentreY = cartesians_->GetHeight() / 2 + centre.y_ * cartesians_->GetScaleY();

		cartesians_->SetX(newCentreX);
		cartesians_->SetY(newCentreY);
	}

	void CartesiansLocator::MoveViewport(float dx, float dy)
	{
		cartesians_->SetX(cartesians_->GetX() + dx);
		cartesians_->SetY(cartesians_->GetY() + dy);
	}

} // Simple2dCharting
