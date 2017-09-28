#include "Basics.h"

namespace Simple2dCharting
{

// Public interface
void GeometryBasics::TransformPoint(
	float vx, float vy, 
	float offsetX, float offsetY, 
	float scaleX, float scaleY, 
	float& x, float& y)
{
	x = offsetX + vx * scaleX;
	y = offsetY - vy * scaleY;
}	

void GeometryBasics::InverseTransform(
		float x, float y, 
		float offsetX, float offsetY, 
		float scaleX, float scaleY, 
		float& vx, float& vy)
{
	vx = (x - offsetX) / scaleX;
	vy = (offsetY - y) / scaleY;
}

} // Simple2dCharting
