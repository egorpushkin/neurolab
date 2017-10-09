#ifndef POINT_H__S2DCHARTING__INCLUDED_
#define POINT_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	template
	<
		class T
	>
	class Point
	{
	public:

		Point();
		Point(T both);
		Point(T x, T y);
		Point(const Point& point);
		virtual ~Point();

		T x_;
		T y_;

	};

	typedef Point< int > IntegerPoint;
	typedef Point< float > FloatPoint;

	typedef Loki::StrongPtr< IntegerPoint > IntegerPointPtr;
	typedef Loki::StrongPtr< FloatPoint > FloatPointPtr;

} // Simple2dCharting

#endif // !POINT_H__S2DCHARTING__INCLUDED_
