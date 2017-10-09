#ifndef PUSHUSERDATA_H__LUAKIT__INCLUDED_
#define PUSHUSERDATA_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class T
	>
	DataWrapper<T>* PushUserData(
		lua_State* L, 
		int stack, 
		T data, 
		char* typeId)
	{
		DataWrapper<T>* pDataWrapper = CreateUserData<T>(L, data);
		
		luaL_newmetatable(L, typeId);
		lua_setmetatable(L, stack);

		return pDataWrapper;
	}

} // namespace LuaKit

#endif // !PUSHUSERDATA_H__LUAKIT__INCLUDED_
