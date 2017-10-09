#pragma once

#include <list>

class Chart
{
	struct Point
	{
		Point() {}
		Point(float x, float y)
			: x_(x)
			, y_(y)
		{}

		float		x_;
		float		y_;
	};

public:
	Chart();
	virtual ~Chart();

	// Public interface
	//////////////////////////////////////////////////////////////////////////
	virtual void				AddPoint(float x, float y);
	
private:
	// Data members
	//////////////////////////////////////////////////////////////////////////
	std::list<Point>			points_;



};
