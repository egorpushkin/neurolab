#include "PrecompiledHeader.h"

#include "AreasTool.h"

#include <limits>

namespace Areas
{
	
	AreasTool::AreasTool()
		: areas_()
	{
	}

	AreasTool::~AreasTool()
	{
		Cleanup();
	}

	// Public interface
	result AreasTool::AllocateAreas(uint areasCount)
	{
		if ( FAILED(Cleanup()) )
			return E_FAIL;

        areas_.resize(areasCount);

		return S_OK;
	}

	result AreasTool::AllocateArea(uint areaIndex, uint pointsCount)
	{
		if ( areaIndex >= areas_.size() )
			return E_FAIL;

		areas_.at(areaIndex).points_.resize(pointsCount);

		return S_OK;
	}

	size_t AreasTool::GetAreasCount()
	{	
        return areas_.size();        
	}

	size_t AreasTool::GetAreaPointsCount(uint areaIndex)
	{
		if ( areaIndex >= areas_.size() )
			return 0;

        return areas_.at(areaIndex).points_.size();
	}

	result AreasTool::CalcBoundary(uint areaIndex)
	{
		if ( areaIndex >= areas_.size() )
			return E_FAIL;

		PointsList_::const_iterator iter = areas_.at(areaIndex).points_.begin();
		PointsList_::const_iterator end = areas_.at(areaIndex).points_.end();

		areas_.at(areaIndex).left_ = std::numeric_limits<uint>::max();
		areas_.at(areaIndex).top_ = std::numeric_limits<uint>::max();
		areas_.at(areaIndex).right_ = std::numeric_limits<uint>::min();
		areas_.at(areaIndex).bottom_ = std::numeric_limits<uint>::min();

		for ( ; iter != end ; ++iter )
		{
			if ( (*iter).x_ < areas_.at(areaIndex).left_ )
				areas_.at(areaIndex).left_ = (*iter).x_;

			if ( (*iter).x_ > areas_.at(areaIndex).right_ )
				areas_.at(areaIndex).right_ = (*iter).x_;

			if ( (*iter).y_ < areas_.at(areaIndex).top_ )
				areas_.at(areaIndex).top_ = (*iter).y_;

			if ( (*iter).y_ > areas_.at(areaIndex).bottom_ )
				areas_.at(areaIndex).bottom_ = (*iter).y_;
		}

		return S_OK;
	}

	result AreasTool::GetAreaBoundary(uint areaIndex, uint& left, uint& top, uint& right, uint& bottom)
	{
		if ( areaIndex >= areas_.size() )
			return E_FAIL;

		left = areas_.at(areaIndex).left_;
		top = areas_.at(areaIndex).top_;
		right = areas_.at(areaIndex).right_;
		bottom = areas_.at(areaIndex).bottom_;

        return S_OK;
	}

	result AreasTool::SetAreaPoint(uint areaIndex, uint pointIndex, uint xcoord, uint ycoord)
	{
		if ( areaIndex >= areas_.size() )
			return E_FAIL;

		if ( pointIndex >= areas_.at(areaIndex).points_.size() )
			return E_FAIL;

		areas_.at(areaIndex).points_.at(pointIndex).x_ = xcoord;
		areas_.at(areaIndex).points_.at(pointIndex).y_ = ycoord;

		return S_OK;
	}

	uint AreasTool::GetAreaPointX(uint areaIndex, uint pointIndex)
	{
		if ( areaIndex >= areas_.size() )
			return 0;

		if ( pointIndex >= areas_.at(areaIndex).points_.size() )
			return 0;

        return areas_.at(areaIndex).points_.at(pointIndex).x_;
	}

	uint AreasTool::GetAreaPointY(uint areaIndex, uint pointIndex)
	{
		if ( areaIndex >= areas_.size() )
			return 0;

		if ( pointIndex >= areas_.at(areaIndex).points_.size() )
			return 0;

		return areas_.at(areaIndex).points_.at(pointIndex).y_;
	}

	result AreasTool::Cleanup()
	{
		areas_.clear();

		return S_OK;
	}

}
