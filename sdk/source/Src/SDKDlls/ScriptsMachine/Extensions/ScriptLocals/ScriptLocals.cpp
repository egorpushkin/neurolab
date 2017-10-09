#include "Common/ScriptsMachine.h"

#include "ScriptLocals.h"

#include "Tools/Lua/Lib.h"
#include "Tools/FileSystem/Path.h"

#include "Location.h"

namespace ScriptsMachine
{

	static const StringA slLibName = "locals";

	// IExtension implementations section		
	result ScriptLocals::EnhanceState(
		ScriptingKit::IScriptRef script, 
		lua_State* L, 
		ScriptingKit::IDataBusRef /* dataBus */)
	{ 
		// Declare API table
		const luaL_reg scriptLocalsLib[] = {
			{"getScriptName",			luaScriptLoacls_getScriptName},
			{NULL, NULL}
		}; 	

		// Register library API
		luaL_openlib(L, slLibName.c_str(), scriptLocalsLib, 0);

		// Declare library strings
		StringVector strings;
		strings.push_back(StringPair("SCR_NAME", script->GetFileName()));
		strings.push_back(StringPair("SCR_DIR", GetFilePath(script->GetFileName())));

		// Register library strings
		RegisterLibStrings(L, slLibName, strings);
	
		return S_FALSE; 
	}

}
