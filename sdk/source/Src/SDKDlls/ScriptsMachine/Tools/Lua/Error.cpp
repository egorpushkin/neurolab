#include "../../Common/ScriptsMachine.h"

#include "Error.h"

namespace ScriptsMachine
{

	result TranslateLuaError(int error)
	{
		result r;

		switch ( error )
		{
		case 0:
			r = S_OK;
			break;
		case LUA_ERRSYNTAX:
			r = ScriptingKit::SCR_E_LUA_ERRSYNTAX;
			break;
		case LUA_ERRMEM:
			r = ScriptingKit::SCR_E_LUA_ERRMEM;
			break;
		case LUA_ERRRUN:
			r = ScriptingKit::SCR_E_LUA_ERRRUN;
			break;
		case LUA_ERRERR:
			r = ScriptingKit::SCR_E_LUA_ERRERR;
			break;
		default:
			r = ScriptingKit::SCR_E_LUA_ERRUNKNOWN;
			break;
		}

		return r;		
	}

	result PopLastError(lua_State* L, StringA& lastError)
	{
		if ( !lua_isstring(L, -1) )
		{
			lastError = "Stack does not contain error code.";
			return ScriptingKit::SCR_E_NO_ERROR_CODE_ON_THE_STACK;
		}

		lastError = lua_tostring(L, -1);
		lua_pop(L, 1);

		return S_OK;
	}

} // namespace ScriptsMachine
