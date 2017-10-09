#ifndef ERROR_H__LUA__SCRIPTSMACHINE__INCLUDED_
#define ERROR_H__LUA__SCRIPTSMACHINE__INCLUDED_

namespace ScriptsMachine
{

	result TranslateLuaError(int error);
	result PopLastError(lua_State* L, StringA& lastError);

} // namespace ScriptsMachine

#endif // !ERROR_H__LUA__SCRIPTSMACHINE__INCLUDED_
