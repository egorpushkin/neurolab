
namespace Simple2dCharting
{

	template< class T >
	Line< T >::Line()
		: begin_()
		, end_()
	{
	}

	template< class T >
	Line< T >::Line(Point_ begin, Point_ end)
		: begin_(begin)
		, end_(end)
	{
	}	

	template< class T >
	Line< T >::Line(T x1, T y1, T x2, T y2)
		: begin_(x1, y1)
		, end_(x2, y2)
	{
	}	

	template< class T >
	Line< T >::~Line()
	{
	}

} // Simple2dCharting
