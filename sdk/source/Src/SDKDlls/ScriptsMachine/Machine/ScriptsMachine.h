#ifndef SCRIPTSMACHINE_ENGINE_H__SCRIPTSMACHINE__INCLUDED_
#define SCRIPTSMACHINE_ENGINE_H__SCRIPTSMACHINE__INCLUDED_

namespace ScriptsMachine
{

	class ScriptsMachine 
		: public MinCOM::CommonImpl< ScriptingKit::IScriptsMachine >
		, public MinCOM::CommonImpl< ScriptingKit::IMaintainer >
	{
	public:
		ScriptsMachine();
		virtual ~ScriptsMachine();

		BEGIN_LOCAL_QI_MAP()
			DECLARE_COMMON(ScriptingKit::IScriptsMachine)
			DECLARE_IID(ScriptingKit::IScriptsMachine, ScriptingKit::IID_IScriptsMachine)
			DECLARE_IID(ScriptingKit::IMaintainer, ScriptingKit::IID_IMaintainer)
		END_LOCAL_QI_MAP()

		// IScriptsMachine declarations section	
		virtual result CreateScript(ScriptingKit::IScriptPtr& script, bool managed);
		virtual result CreateDataBus(ScriptingKit::IDataBusPtr& dataBus);

		// IMaintainer declarations section	
		virtual result Lock();
		virtual result Unlock();
		virtual uint GetScriptsCount();
		virtual ScriptingKit::IScriptPtr GetScriptAt(uint scriptIndex);
		virtual result RegisterScript(const ScriptingKit::IScriptPtr& script);
		virtual result UnregisterScript(const ScriptingKit::IScriptPtr& script);	

		// ICommon declarations section	
		virtual result QueryInterface(REFIID iid, void** ppObject);

	private:
		
		/**
		 * Synchronization object.
		 */		 
		ost::Mutex syncObject_;




	};

}

#endif // !SCRIPTSMACHINE_ENGINE_H__SCRIPTSMACHINE__INCLUDED_
