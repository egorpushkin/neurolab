#include "PrecompiledHeader.h"

#include "AreasTool/AreasTool.h"

#include "Geometry.h"

namespace Generator
{

	// Public interface
	int GeometryTool::CrossedTool(int ax, int ay, int bx, int by, int tx, int ty)
	{
		return tx * (by - ay) + ty * (ax - bx) + ay * bx - ax * by;
	}

	bool GeometryTool::IsCrossed(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	{
		if 
		( 
			(
				CrossedTool(x1, y1, x2, y2, x3, y3) * 
				CrossedTool(x1, y1, x2, y2, x4, y4) < 0
			) && (
				CrossedTool(x3, y3, x4, y4, x1, y1) * 
				CrossedTool(x3, y3, x4, y4, x2, y2) < 0
			)
		)
			return true;
		else
			return false;
	}

	bool GeometryTool::IsPointInArea(Areas::AreasTool* pAreasTool, uint areaIndex, int x, int y)
	{
		uint crossesCount = 0;

		for ( uint i = 0 ; i < pAreasTool->GetAreaPointsCount(areaIndex) - 1 ; ++i )
		{
			if ( IsCrossed(
				pAreasTool->GetAreaPointX(areaIndex, i),
				pAreasTool->GetAreaPointY(areaIndex, i),
				pAreasTool->GetAreaPointX(areaIndex, i + 1),
				pAreasTool->GetAreaPointY(areaIndex, i + 1),
				x, y, 0, y) )
			{
				++crossesCount;
			}
		}

		uint lastIndex = (uint)pAreasTool->GetAreaPointsCount(areaIndex) - 1;
		if ( IsCrossed(
			pAreasTool->GetAreaPointX(areaIndex, lastIndex),
			pAreasTool->GetAreaPointY(areaIndex, lastIndex),
			pAreasTool->GetAreaPointX(areaIndex, 0),
			pAreasTool->GetAreaPointY(areaIndex, 0),
			x, y, 0, y) )
		{
			++crossesCount;
		}

		if ( crossesCount % 2 == 1 ) // math.mod(crosses_count, 2) == 1 
			return true;
		else
			return false;    
	}

	bool GeometryTool::IsSquareInArea(Areas::AreasTool* pAreasTool, uint areaIndex, int x1, int y1, int x2, int y2)
	{
		if ( IsPointInArea(pAreasTool, areaIndex, x1, y1) &&
			IsPointInArea(pAreasTool, areaIndex, x2, y1) &&
			IsPointInArea(pAreasTool, areaIndex, x2, y2) &&
			IsPointInArea(pAreasTool, areaIndex, x1, y2) )
			return true;
		else
			return false;     
	}

}
