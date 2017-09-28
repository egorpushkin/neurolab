#ifndef DRAWING_H__LUA_PACKAGE__INCLUDED_
#define DRAWING_H__LUA_PACKAGE__INCLUDED_

namespace Drawing
{

	class DrawingPackage : public LuaKit::PackageImpl 
	{
	public:		
		DrawingPackage();
	};

	typedef Loki::SingletonHolder< DrawingPackage > DrawingPackageSngl;

} // namespace Drawing

#endif // !DRAWING_H__LUA_PACKAGE__INCLUDED_
