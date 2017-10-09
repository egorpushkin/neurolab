#ifndef DBSCAN_H__DBSCAN__LTILIB__LUA_PACKAGE__INCLUDED_
#define DBSCAN_H__DBSCAN__LTILIB__LUA_PACKAGE__INCLUDED_

namespace LTILib
{

	DECLARE_API(
		DBScanL1Distantor, 
		lti::DBScan< lti::l1Distantor< lti::dvector > >, 
		LTILibPackageSngl);
	
	DECLARE_API(
		DBScanL2Distantor, 
		lti::DBScan< lti::l2Distantor< lti::dvector > >, 
		LTILibPackageSngl);
	
	DECLARE_API(
		DBScanL2SquareDistantor, 
		lti::DBScan< lti::l2SquareDistantor< lti::dvector > >, 
		LTILibPackageSngl);

} // namespace LTILib

#endif // !DBSCAN_H__DBSCAN__LTILIB__LUA_PACKAGE__INCLUDED_
