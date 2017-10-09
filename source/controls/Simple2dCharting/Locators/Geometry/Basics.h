#ifndef BASICS_H__GEOMETRY__S2DCHARTING__INCLUDED_
#define BASICS_H__GEOMETRY__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class GeometryBasics
	{
	public:

		// Public interface
		static void TransformPoint(
			float vx, float vy, 
			float offsetX, float offsetY, 
			float scaleX, float scaleY, 
            float& x, float& y);

		static void InverseTransform(
			float x, float y, 
			float offsetX, float offsetY, 
			float scaleX, float scaleY, 
			float& vx, float& vy);

		
	}; // GeometryBasics

} // Simple2dCharting

#endif // !BASICS_H__GEOMETRY__S2DCHARTING__INCLUDED_
