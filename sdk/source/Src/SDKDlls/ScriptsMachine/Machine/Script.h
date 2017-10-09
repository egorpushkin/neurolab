#ifndef SCRIPT_H__SCRIPTSMACHINE__INCLUDED_
#define SCRIPT_H__SCRIPTSMACHINE__INCLUDED_

namespace ScriptsMachine
{

class Script
	: public MinCOM::CommonImpl< ScriptingKit::IScript >
	, public MinCOM::CommonImpl< ScriptingKit::IExtensionsMng >
{

	BEGIN_LOCAL_QI_MAP()
		DECLARE_COMMON(ScriptingKit::IScript)
		DECLARE_IID(ScriptingKit::IScript, ScriptingKit::IID_IScript)
		DECLARE_IID(ScriptingKit::IExtensionsMng, ScriptingKit::IID_IExtensionsMng)
	END_LOCAL_QI_MAP()

public:
	Script();
	virtual ~Script();

	// IScript declarations section	
	virtual result LoadFile(const StringA& filename, bool execute);
	virtual result LoadString(const StringA& buffer, bool execute);
	virtual StringA GetFileName();
	virtual StringA GetLastError();
	virtual result GetLastErrorResult();
	virtual result Execute();
	virtual bool IsRunning();
	virtual result AttachBus(const ScriptingKit::IDataBusPtr& dataBus);    
	virtual ScriptingKit::IDataBusPtr GetDataBus();    

	// IExtensionsMng declarations section	
	virtual result Register(const ScriptingKit::IExtensionPtr& extension);   

	// ICommon declarations section	
	virtual result QueryInterface(REFIID iid, void** ppObject);

private:

	bool IsStateCreated();
	bool IsReadyToBeExecuted();

	result DoLoadData(bool fromFile, const StringA& dataBuffer, bool execute);
	result DoExecuteScript();

	result CreateEmptyState();
	result ReleaseExistentState();

	void SetRunning();
	void SetTerminated();

	result InstallExtensions(bool install);

	void SetLastError(const StringA& lastError, result r);

private:

	ost::Mutex syncObject_;

	ScriptingKit::IDataBusPtr dataBus_;

	lua_State* pLuaState_;

	StringA filename_;
	StringA lastError_;
	result lastErrorResult_;

	bool isRunning_;
	bool readyToBeExecuted_;

	typedef std::vector< ScriptingKit::IExtensionPtr > ExtensionsContainer;
	ExtensionsContainer extensions_;

};

}

#endif // !SCRIPT_H__SCRIPTSMACHINE__INCLUDED_
