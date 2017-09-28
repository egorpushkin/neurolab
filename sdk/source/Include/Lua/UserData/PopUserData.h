#ifndef POPUSERDATA_H__LUAKIT__INCLUDED_
#define POPUSERDATA_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class T
	>
	T PopUserData(
		lua_State* L, 
		int stack, 
		char* typeId)
	{
		if ( lua_type(L, stack) != LUA_TUSERDATA )
			return T();

		void* pUnknownWrapper = luaL_checkudata(L, stack, typeId);
		if( !pUnknownWrapper )
			return T();

		return UnwrapData<T>(pUnknownWrapper);
	}

} // namespace LuaKit

#endif // !POPUSERDATA_H__LUAKIT__INCLUDED_
