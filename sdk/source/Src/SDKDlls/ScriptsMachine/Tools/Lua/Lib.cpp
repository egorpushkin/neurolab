#include "Common/ScriptsMachine.h"

#include "Lib.h"

namespace ScriptsMachine
{

	bool IsLibRegistered(lua_State* L, const StringA& name)
	{
		lua_getglobal(L, name.c_str());
		return lua_istable(L, -1) ? ( true ) : ( false );
	}

	void RegisterLibNumerics(lua_State* L, const StringA& libName, NumericVectorRef muns)
	{
		lua_pushstring(L, libName.c_str());
		lua_gettable(L, LUA_GLOBALSINDEX);  
		lua_insert(L, -1);

		NumericVector::const_iterator iter = muns.begin();
		NumericVector::const_iterator end = muns.end();

		for ( ; iter != end; ++iter ) 
		{
			lua_pushstring(L, (*iter).first.c_str());
			lua_pushnumber(L, (*iter).second);
			lua_settable(L, -3);
		} 

		lua_pop(L, 0);			
	}

	void RegisterLibStrings(lua_State* L, const StringA& libName, StringVectorRef strings)
	{
		lua_pushstring(L, libName.c_str());
		lua_gettable(L, LUA_GLOBALSINDEX);  
		lua_insert(L, -1);

		StringVector::const_iterator iter = strings.begin();
		StringVector::const_iterator end = strings.end();

		for ( ; iter != end; ++iter ) 
		{
			lua_pushstring(L, (*iter).first.c_str());
			lua_pushstring(L, (*iter).second.c_str());
			lua_settable(L, -3);
		} 

		lua_pop(L, 0);	
	}

} // namespace ScriptsMachine
