#ifndef LINE_H__S2DCHARTING__INCLUDED_
#define LINE_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	template
	<
		class T
	>
	class Line
	{
	public:

		typedef Point< T > Point_;

		Line();
		Line(Point_ begin, Point_ end);
		Line(T x1, T y1, T x2, T y2);
		virtual ~Line();

		Point< T > begin_;
		Point< T > end_;

	};

	typedef Line< int > IntegerLine;
	typedef Line< float > FloatLine;

	typedef Loki::StrongPtr< IntegerLine > IntegerLinePtr;
	typedef Loki::StrongPtr< FloatLine > FloatLinePtr;

} // Simple2dCharting

#endif // !LINE_H__S2DCHARTING__INCLUDED_
