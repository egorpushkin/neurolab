#ifndef AREASTOOL_H__AREASTOOL__INCLUDED_
#define AREASTOOL_H__AREASTOOL__INCLUDED_

namespace Areas
{

	// AreasTool declaration
	class AreasTool 
	{
	public:

		AreasTool();
		~AreasTool();

		// Public interface
		result AllocateAreas(uint areasCount);
		result AllocateArea(uint areaIndex, uint pointsCount);

		size_t GetAreasCount();
		size_t GetAreaPointsCount(uint areaIndex);

		result CalcBoundary(uint areaIndex);

		result GetAreaBoundary(uint areaIndex, uint& left, uint& top, uint& right, uint& bottom);
        
		result SetAreaPoint(uint areaIndex, uint pointIndex, uint xcoord, uint ycoord);
		
		uint GetAreaPointX(uint areaIndex, uint pointIndex);
		uint GetAreaPointY(uint areaIndex, uint pointIndex);

		result Cleanup();

	private:

		struct Point_
		{
			uint x_;
			uint y_;
		};

		typedef std::vector< Point_ > PointsList_;

		struct Area_
		{
			uint left_;
			uint top_;
			uint right_;
			uint bottom_;		

			PointsList_ points_;            
		};

		typedef std::vector< Area_ > AreasList_;

		AreasList_ areas_;

	};

}

#endif // !AREASTOOL_H__AREASTOOL__INCLUDED_

