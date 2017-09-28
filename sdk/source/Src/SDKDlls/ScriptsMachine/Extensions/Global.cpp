#include "../Common/ScriptsMachine.h"

#include "Global.h"

namespace ScriptsMachine
{

	// IExtension implementations section		
	result Global::EnhanceState(ScriptingKit::IScriptRef /* script */, lua_State* /* L */, ScriptingKit::IDataBusRef /* dataBus */)
	{ 
		



		return S_FALSE; 
	}

}
