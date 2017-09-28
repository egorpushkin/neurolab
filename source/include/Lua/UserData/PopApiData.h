#ifndef POPAPIDATA_H__LUAKIT__INCLUDED_
#define POPAPIDATA_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class ApiSnglClass
	> 
	typename ApiSnglClass::ObjectType::Type_ PopApiData(
		lua_State* L, 
		int stack = 1)
	{
		try
		{
			LuaKit::DataWrapper< ApiSnglClass::ObjectType::Type_ >* pDataWrapper =	
				(LuaKit::DataWrapper< ApiSnglClass::ObjectType::Type_ >*)							
					auxiliar_checkclass(
						L, 
						ApiSnglClass::Instance().GetClassName(), 
						stack);					

			if ( !pDataWrapper ) 									
			{
				luaL_argerror(L, stack, "Wrong userdata wrapper");	
				throw std::exception("Wrong userdata wrapper");
			}
			
			if ( !pDataWrapper->GetData() )		
			{
				luaL_argerror(L, stack, "Wrong userdata object");	
				throw std::exception("Wrong userdata object");
			}

			return pDataWrapper->GetData();	
		}
		catch ( ... )
		{			
		}

		return ApiSnglClass::ObjectType::Type_();
	}

} // namespace LuaKit

#endif // !POPAPIDATA_H__LUAKIT__INCLUDED_
