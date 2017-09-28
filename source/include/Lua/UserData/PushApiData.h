#ifndef PUSHAPIDATA_H__LUAKIT__INCLUDED_
#define PUSHAPIDATA_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class ApiSnglClass
	> 
	void PushApiData(
		lua_State* L, 
		typename ApiSnglClass::ObjectType::Type_ data,
		int stack = -1)
	{
		try
		{
			PUSH_AUXILIAR(
				ApiSnglClass::ObjectType::Type_, 
				data,
				ApiSnglClass::Instance().GetClassName(),
				stack);
		}
		catch ( ... )
		{			
		}
	}

} // namespace LuaKit

#endif // !PUSHAPIDATA_H__LUAKIT__INCLUDED_
