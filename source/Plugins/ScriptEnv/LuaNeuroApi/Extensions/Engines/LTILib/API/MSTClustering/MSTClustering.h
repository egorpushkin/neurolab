#ifndef MSTCLUSTERING_H__MSTCLUSTERING__LTILIB__LUA_PACKAGE__INCLUDED_
#define MSTCLUSTERING_H__MSTCLUSTERING__LTILIB__LUA_PACKAGE__INCLUDED_

namespace LTILib
{
	
	DECLARE_API(
		MSTClusteringL2SquareDistantor, 
		lti::MSTClustering< lti::l2SquareDistantor< lti::dvector > >, 
		LTILibPackageSngl);

} // namespace LTILib

#endif // !MSTCLUSTERING_H__MSTCLUSTERING__LTILIB__LUA_PACKAGE__INCLUDED_
