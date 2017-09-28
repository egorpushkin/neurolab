
namespace Simple2dCharting
{

	template< class T >
	Point< T >::Point()
		: x_()
		, y_()
	{
	}

	template< class T >
	Point< T >::Point(T x, T y)
		: x_(x)
		, y_(y)
	{
	}	

	template< class T >
	Point< T >::Point(T both)
		: x_(both)
		, y_(both)
	{
	}	

	template< class T >
	Point< T >::Point(const Point& point)
		: x_(point.x_)
		, y_(point.y_)
	{
	}

	template< class T >
	Point< T >::~Point()
	{
	}

} // Simple2dCharting
