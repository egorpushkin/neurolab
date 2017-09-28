#ifndef CREATEUSERDATA_H__LUAKIT__INCLUDED_
#define CREATEUSERDATA_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class T
	> 
	DataWrapper<T>* CreateUserData(
		lua_State* L, 
		T data)
	{
		DataWrapper<T>* pDataWrapper = 
			static_cast< DataWrapper<T>* > ( 
				lua_newuserdata(L, sizeof( DataWrapper<T> ) ) 
			);

        pDataWrapper->SetData(data);

		return pDataWrapper;
	}

} // namespace LuaKit

#endif // !CREATEUSERDATA_H__LUAKIT__INCLUDED_
