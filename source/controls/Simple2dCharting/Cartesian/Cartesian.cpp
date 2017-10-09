#include "Common/Includes.h"

#include "Cartesian.h"

namespace Simple2dCharting
{

	CartesianCoordinates::CartesianCoordinates()
		: width_(0.0f)
		, height_(0.0f)
		, x_(0.0f)
		, y_(0.0f)
		, scaleX_(1.0f)
		, scaleY_(1.0f)
	{
	}
	
	CartesianCoordinates::~CartesianCoordinates()
	{
	}

	// Public interface
	void CartesianCoordinates::SetWidth(float width)
	{
		width_ = width;
	}

	float CartesianCoordinates::GetWidth() const
	{
		return width_;
	}

	void CartesianCoordinates::SetHeight(float height)
	{
		height_ = height;
	}

	float CartesianCoordinates::GetHeight() const
	{
		return height_;
	}

	void CartesianCoordinates::SetX(float x)
	{
		x_ = x;
	}

	float CartesianCoordinates::GetX() const
	{
		return x_;
	}

	void CartesianCoordinates::SetY(float y)
	{
		y_ = y;
	}

	float CartesianCoordinates::GetY() const
	{
		return y_;
	}

	void CartesianCoordinates::SetScaleX(float scaleX)
	{
		scaleX_ = scaleX;
	}

	float CartesianCoordinates::GetScaleX() const
	{
		return scaleX_;
	}

	void CartesianCoordinates::SetScaleY(float scaleY)
	{
		scaleY_ = scaleY;
	}

	float CartesianCoordinates::GetScaleY() const
	{
		return scaleY_;
	}

	void CartesianCoordinates::SetScale(float scale)
	{
		scaleX_ = scale;
		scaleY_ = scale;
	}

	float CartesianCoordinates::GetScale()
	{
		return scaleX_;
	}

} // Simple2dCharting
