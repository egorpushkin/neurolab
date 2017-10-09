#ifndef CHARTS_H__S2DCHARTING__INCLUDED_
#define CHARTS_H__S2DCHARTING__INCLUDED_

#include "External/fast_mutex.h"

#include "Common/BasicChart.h"

#include "Common/ContainerChart.h"

#include "Point.h"

#include "Line.h"

namespace Simple2dCharting 
{

	typedef ContainerChart< IntegerPoint > IntegerPointChart;
	typedef ContainerChart< FloatPoint > FloatPointChart;

	typedef Loki::StrongPtr< FloatPointChart > FloatPointChartPtr;
	typedef const FloatPointChartPtr& FloatPointChartRef;

} // Simple2dCharting

#endif // !CHARTS_H__S2DCHARTING__INCLUDED_
