#ifndef CARTESIAN_H__S2DCHARTING__INCLUDED_
#define CARTESIAN_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class CartesianCoordinates
	{
	public:

		CartesianCoordinates();
		virtual ~CartesianCoordinates();

		// Public interface
		virtual void SetWidth(float width);
		virtual float GetWidth() const;

		virtual void SetHeight(float height);
		virtual float GetHeight() const;

		virtual void SetX(float x);
		virtual float GetX() const;

		virtual void SetY(float y);
		virtual float GetY() const;

		virtual void SetScaleX(float scaleX);
		virtual float GetScaleX() const;

		virtual void SetScaleY(float scaleY);
		virtual float GetScaleY() const;

		virtual void SetScale(float scale);
		virtual float GetScale();

	private:

		// Viewport characteristics
		float width_;
		float height_;

		// Viewport position
		float x_;
		float y_;

		// Scale
		float scaleX_;
		float scaleY_;

	}; // CartesianCoordinates

	typedef Loki::StrongPtr< CartesianCoordinates > CartesianCoordinatesPtr;
	typedef Loki::StrongPtr< CartesianCoordinates, false > CartesianCoordinatesWeak;
	typedef const CartesianCoordinatesPtr& CartesianCoordinatesRef;

} // Simple2dCharting

#endif // !CARTESIAN_H__S2DCHARTING__INCLUDED_
