#ifndef GEOMETRY_H__DATAGENERATOR__INCLUDED_
#define GEOMETRY_H__DATAGENERATOR__INCLUDED_

namespace Generator
{

	// GeometryTool declaration
	class GeometryTool 
	{
	public:

		// Public interface
		static bool IsSquareInArea(Areas::AreasTool* pAreasTool, uint areaIndex, int x1, int y1, int x2, int y2); 		

	private:

		// Private interface
		static int CrossedTool(int ax, int ay, int bx, int by, int tx, int ty); 		
		static bool IsCrossed(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4); 
		static bool IsPointInArea(Areas::AreasTool* pAreasTool, uint areaIndex, int x, int y); 

	};

}

#endif // !GEOMETRY_H__DATAGENERATOR__INCLUDED_
