#ifndef TOOLS_H__SOFM2D__LTILIB__LUA_PACKAGE__INCLUDED_
#define TOOLS_H__SOFM2D__LTILIB__LUA_PACKAGE__INCLUDED_

namespace LTILib
{

	lti::SOFM::parameters::eInit sofm2d_tools_IntToeInit(int method);
	lti::SOFM::parameters::eMetric sofm2d_tools_IntToeMetric(int metric);

} // namespace LTILib

#endif // !TOOLS_H__SOFM2D__LTILIB__LUA_PACKAGE__INCLUDED_
