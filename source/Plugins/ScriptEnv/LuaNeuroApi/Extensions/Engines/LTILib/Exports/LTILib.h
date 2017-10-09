#ifndef LTILIB_H__LUA_PACKAGE__INCLUDED_
#define LTILIB_H__LUA_PACKAGE__INCLUDED_

namespace LTILib
{

	class LTILibPackage : public LuaKit::PackageImpl 
	{
	public:		
		LTILibPackage();
	};

	typedef Loki::SingletonHolder< LTILibPackage > LTILibPackageSngl;

} // namespace LTILib

#endif // !LTILIB_H__LUA_PACKAGE__INCLUDED_
