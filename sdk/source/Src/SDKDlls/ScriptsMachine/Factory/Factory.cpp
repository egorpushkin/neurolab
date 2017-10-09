#include "../Common/ScriptsMachine.h"

#include "Factory.h"

#include "../Environment/CommonFactory.h"
#include "../Machine/ScriptsMachine.h"
#include "../Machine/Script.h"
#include "../Bus/DataBus.h"

#include "../Extensions/Global.h"
#include "../Extensions/ScriptLocals/ScriptLocals.h"
#include "../Extensions/Threading/Threading.h"

#include "../Setup/Creators.h"

namespace ScriptsMachine
{

	namespace Private
	{

		inline result RegisterEntries()		
		{
			static bool registered = false;
			if (registered)
				return S_FALSE;

			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_ScriptsFactory, MinCOM::ObjectCreator<CommonFactory>);
			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_Script, MinCOM::ObjectCreator<Script>);
			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_AdvancedScript, CreateScript);
			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_ScriptsMachine, MinCOM::ObjectCreator<ScriptsMachine>);
			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_DataBus, MinCOM::ObjectCreator<DataBus>);

			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_ExtGlobal, MinCOM::ObjectCreator<Global>);
			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_ExtScriptLocals, MinCOM::ObjectCreator<ScriptLocals>);
			MinCOM::GetCommonFactory().Register(ScriptingKit::CLSID_ExtThreading, MinCOM::ObjectCreator<Threading>);

			registered = true;
			return S_OK;
		}

	}

	MinCOM::ICommonPtr CreateObject(REFCLSID clsid)
	{
		if (FAILED(Private::RegisterEntries()))
			return NULL;

		return MinCOM::GetCommonFactory().CreateObject(clsid);
	}

}
