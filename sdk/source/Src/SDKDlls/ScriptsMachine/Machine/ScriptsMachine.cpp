#include "../Common/ScriptsMachine.h"

#include "ScriptsMachine.h"

#include "../Factory/Factory.h"

namespace ScriptsMachine
{

extern ulong objCount;

ScriptsMachine::ScriptsMachine()
	: syncObject_()
{
	++objCount;
}

ScriptsMachine::~ScriptsMachine()
{
	--objCount;
}

// IScriptsMachine implementations section	
result ScriptsMachine::CreateScript(ScriptingKit::IScriptPtr& script, bool managed)
{
	ost::MutexLock locker(syncObject_);

	try
	{
		script = ScriptingKit::IScriptPtr(
			CreateObject(ScriptingKit::CLSID_AdvancedScript), 
			ScriptingKit::IID_IScript
		);
	
		if ( script && managed )
		{
			result r = RegisterScript(script);
			
			if ( FAILED(r) )
				return r;
		}

		return ( script ) ? ( S_OK ) : ( E_FAIL );
	} 
	catch (...)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

result ScriptsMachine::CreateDataBus(ScriptingKit::IDataBusPtr& dataBus)
{
	ost::MutexLock locker(syncObject_);

	try
	{
		dataBus = ScriptingKit::IDataBusPtr(
			CreateObject(ScriptingKit::CLSID_DataBus), 
			ScriptingKit::IID_IDataBus
		);

		return ( dataBus ) ? ( S_OK ) : ( E_FAIL );
	} 
	catch (...)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

// IMaintainer implementations section	
result ScriptsMachine::Lock()
{
	syncObject_.enter();
	
	return S_OK;
}

result ScriptsMachine::Unlock()
{
	syncObject_.leave();

	return S_OK;
}

uint ScriptsMachine::GetScriptsCount()
{
	return 0;
}

ScriptingKit::IScriptPtr ScriptsMachine::GetScriptAt(uint /* scriptIndex */)
{
	return NULL;
}

result ScriptsMachine::RegisterScript(const ScriptingKit::IScriptPtr& /* script */)
{
	return E_NOTIMPL;
}

result ScriptsMachine::UnregisterScript(const ScriptingKit::IScriptPtr& /* script */)
{
	return E_NOTIMPL;
}	

// ICommon implementations section	
result ScriptsMachine::QueryInterface(REFIID iid, void** ppObject)
{
	LOCAL_QI(iid, ppObject);

	*ppObject = NULL;
	return E_NOINTERFACE;
}

}
