#ifndef GETPARAMSCOUNT_H__LUAKIT__INCLUDED_
#define GETPARAMSCOUNT_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	inline unsigned int GetParamsCount(lua_State* L)
	{
		return lua_gettop(L);
	}

} // namespace LuaKit

#endif // !GETPARAMSCOUNT_H__LUAKIT__INCLUDED_
