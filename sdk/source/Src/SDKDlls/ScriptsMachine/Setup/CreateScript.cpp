#include "../Common/ScriptsMachine.h"

#include "Creators.h"

#include "../Factory/Factory.h"

#include "../Machine/Script.h"

namespace ScriptsMachine
{

	// Tools
	//////////////////////////////////////////////////////////////////////////
	result RegisterExtension(const ScriptingKit::IExtensionsMngPtr& scriptExt, REFCLSID clsid)										\
	{
		return scriptExt->Register(												
			ScriptingKit::IExtensionPtr(									
				CreateObject(clsid),										
				ScriptingKit::IID_IExtension								
			)																
		);
	}

	// Creator routine
	//////////////////////////////////////////////////////////////////////////
	ICommonPtr CreateScript()
	{
		// Create basic script object
		ScriptingKit::IScriptPtr script = ScriptingKit::IScriptPtr(
			CreateObject(ScriptingKit::CLSID_Script), ScriptingKit::IID_IScript);

		ScriptingKit::IExtensionsMngPtr scriptExt = ScriptingKit::IExtensionsMngPtr(
			script, ScriptingKit::IID_IExtensionsMng);

		// Register core extensions
		RegisterExtension(scriptExt, ScriptingKit::CLSID_ExtGlobal);
		RegisterExtension(scriptExt, ScriptingKit::CLSID_ExtScriptLocals);
		


		


		
		// Creator must return strong shared pointer of ICommon control interface.
		return ICommonPtr(script, MinCOM::IID_ICommon);
	}

}
