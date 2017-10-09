#include "Common/ScriptsMachine.h"

#include "Script.h"

#include "Tools/Lua/Error.h"

namespace ScriptsMachine
{

const bool LOAD_FROM_FILE = true;
const bool LOAD_FROM_STRING = false;

const bool INSTALL = true;
const bool UNINSTALL = false;
	
extern ulong objCount;

Script::Script()
	: syncObject_()
	, dataBus_()
	, pLuaState_(NULL)
	, filename_()
	, lastError_()
	, lastErrorResult_()
	, isRunning_(false)
	, readyToBeExecuted_(false)
	, extensions_()
{
    if ( FAILED(CreateEmptyState()) )
		throw ScriptingKit::CoreException();

	++objCount;
}

Script::~Script()
{
	try
	{
		ReleaseExistentState();
	}
	catch ( ... )
	{
		/**
		 * Do nothing here. Just catch all possible exceptions to avoid 
		 * abnormal program termination during stack folding.
		 */
	}

	--objCount;
}

// IScript implementations section	
result Script::LoadFile(const StringA& filename, bool execute)
{
	return DoLoadData(LOAD_FROM_FILE, filename, execute);
}

result Script::LoadString(const StringA& buffer, bool execute)
{
	return DoLoadData(LOAD_FROM_STRING, buffer, execute);
}

StringA Script::GetFileName()
{
	return filename_;
}

StringA Script::GetLastError()
{
	return lastError_;
}

result Script::GetLastErrorResult()
{
	return lastErrorResult_;
}

result Script::Execute()
{
	return DoExecuteScript();
}

bool Script::IsRunning()
{
	ost::MutexLock locker(syncObject_);

	return isRunning_;
}

result Script::AttachBus(const ScriptingKit::IDataBusPtr& dataBus)
{
	ost::MutexLock locker(syncObject_);

	if ( IsRunning() )
		return ScriptingKit::SCR_E_ALREADY_EXECUTED;

	dataBus_ = dataBus;

	return S_OK;
}

ScriptingKit::IDataBusPtr Script::GetDataBus()
{
	return dataBus_;
}

// IExtensionsMng implementations section	
result Script::Register(const ScriptingKit::IExtensionPtr& extension)
{
	ost::MutexLock locker(syncObject_);

	extensions_.push_back(extension);

	return S_OK;
}

// ICommon implementations section	
result Script::QueryInterface(REFIID iid, void** ppObject)
{
	ost::MutexLock locker(syncObject_);

	LOCAL_QI(iid, ppObject);

	*ppObject = NULL;
	return E_NOINTERFACE;
}

// Private tools
//////////////////////////////////////////////////////////////////////////
bool Script::IsStateCreated()
{
	return ( pLuaState_ != NULL );
}

bool Script::IsReadyToBeExecuted()
{
	return readyToBeExecuted_;
}

result Script::DoLoadData(bool fromFile, const StringA& dataBuffer, bool execute)
{
	ost::MutexLock locker(syncObject_);

	if ( IsReadyToBeExecuted() )
		return ScriptingKit::SCR_E_ALREADY_LOADED;	

	if ( IsRunning() )
		return ScriptingKit::SCR_E_ALREADY_EXECUTED;

	if ( !IsStateCreated() )
	{
		result r = CreateEmptyState();
		if ( FAILED(r) )
			return r;
	}

	SetLastError("", S_OK);

	if ( fromFile )
		filename_ = dataBuffer;

	if ( FAILED(InstallExtensions(INSTALL)) )
		return ScriptingKit::SCR_E_FAILED_TO_INSTALL_EXTENSIONS;

	readyToBeExecuted_ = false;

	int error = 0;
	if (fromFile)
		error = luaL_loadfile(pLuaState_, dataBuffer.c_str());
	else 
		error = luaL_loadstring(pLuaState_, dataBuffer.c_str());

	result r = TranslateLuaError(error);
	if ( FAILED(r) )
	{
		PopLastError(pLuaState_, lastError_);
		lastErrorResult_ = r;

		return ScriptingKit::SCR_E_COMPILATION;
	}

	readyToBeExecuted_ = true;

	if ( !execute )
		return S_OK;

	return DoExecuteScript();
}

result Script::DoExecuteScript()
{
	ost::MutexLock locker(syncObject_);

	if ( !IsStateCreated() )
		return ScriptingKit::SCR_E_NOTHING_TO_EXECUTE;
	
	if ( !IsReadyToBeExecuted() )
		return ScriptingKit::SCR_E_NOT_LOADED;	

	if ( IsRunning() )
		return ScriptingKit::SCR_E_ALREADY_EXECUTED;

	readyToBeExecuted_ = false;
	
	try
	{
		SetRunning();

		int error = lua_pcall(pLuaState_, 0, 0, 0);

		SetTerminated();

		result r = TranslateLuaError(error);
		if ( FAILED(r) )
		{
			PopLastError(pLuaState_, lastError_);
			lastErrorResult_ = r;

			return ScriptingKit::SCR_E_EXECUTION;
		}	
	} 
	catch ( ... )
	{
		SetTerminated();

		return ScriptingKit::SCR_E_EXCEPTION_DURING_EXECUTION;
	}

	return S_OK;
}

result Script::CreateEmptyState()
{
	if ( IsStateCreated() )
		ReleaseExistentState();

	pLuaState_ = lua_open();

	return ( pLuaState_ ) ? ( S_OK ) : ( ScriptingKit::SCR_E_FAILED_TO_CREATE_EMPTY_STATE );
}

result Script::ReleaseExistentState()
{
	if ( !IsStateCreated() )
		return S_FALSE;

	lua_close(pLuaState_);
	pLuaState_ = NULL;

    return S_OK;
}

void Script::SetRunning()
{
	isRunning_ = true;
}

void Script::SetTerminated()
{
	isRunning_ = false;
}

result Script::InstallExtensions(bool install)
{	
	if ( !IsStateCreated() )		
		return ScriptingKit::SCR_E_NOTHING_TO_EXECUTE;

	luaL_openlibs(pLuaState_);

	result r;

	ExtensionsContainer::const_iterator iter = extensions_.begin();
	ExtensionsContainer::const_iterator end = extensions_.end();

	for ( ; iter != end; ++iter)
	{
		r = S_OK;

		if (install)
			r = (*iter)->EnhanceState(
				ScriptingKit::IScriptPtr(this, ScriptingKit::IID_IScript), 
				pLuaState_, 
				dataBus_);

		if ( FAILED(r) )
			return r;
	}

	return S_OK;
}

void Script::SetLastError(const StringA& lastError, result r)
{
	lastError_ = lastError;
	lastErrorResult_ = r;
}

}
