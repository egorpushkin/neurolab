#include "stdafx.h"

#include "Chart.h"

Chart::Chart()
{

}

Chart::~Chart()
{

}


// Public interface
//////////////////////////////////////////////////////////////////////////
void Chart::AddPoint(float x, float y)
{
	points_.push_back(Point(x, y));
}