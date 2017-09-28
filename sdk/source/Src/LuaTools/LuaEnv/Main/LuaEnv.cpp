#include "../Common/Includes.h"

#include "../Env/LuaEnvCmd.h"

using namespace ScriptingKit;
using namespace ConsoleHelpersKit;

typedef MinCOM::ComPtr< ComponentsKit::IComponentLoader > IComponentLoaderPtr;

class LuaEnv
	: public Application
{
	// Forced declaration of assignment operators
	LuaEnv(const LuaEnv&);
	const LuaEnv& operator =(const LuaEnv&);

public:
	LuaEnv()
		: loader_(CConstructTool<ComponentsKit::CComponentLoader, ComponentsKit::IComponentLoader>::
			ConstructObject(ComponentsKit::IID_IComponentLoader))
	{
		if ( !loader_ )
			throw ConsoleException("Error creating core object ComponentLoader.");

		loader_->SetLibraryName(StringA("./ScriptsMachine") + SO_LIB_EXT);
		result resultCode = loader_->InitializeComponentInstance(CLSID_ScriptsFactory);
		if ( FAILED(resultCode) )
			throw ConsoleException("ScriptsMachine component cannot be loaded.");
	}
	virtual ~LuaEnv()
	{
	}

	virtual result Process()
	{
		IScriptsMachinePtr machine;
		result resultCode = loader_->QueryComponentObject(IID_IScriptsMachine, (void**)&GetImplRef(machine));
		if ( FAILED(resultCode) )
		{
			Console::EventNotify("Error: Query request for IScriptsMachine control interface failed."); 
			return E_FAIL;
		}

		IScriptPtr script = NULL;
		resultCode = machine->CreateScript(script, false);
		if ( FAILED(resultCode) )
		{
			Console::EventNotify("Error: Failed to create unmanaged script object."); 
			return E_FAIL;
		}

		resultCode = script->LoadFile(CommandLine::Instance().GetOperand('s'), true);
		if ( FAILED(resultCode) )
		{
			if ( resultCode == SCR_E_COMPILATION )
				Console::EventNotify("Compilation error:"); 
			else if ( resultCode == SCR_E_EXECUTION )
				Console::EventNotify("Execution error:"); 
			else if ( resultCode == SCR_E_EXCEPTION_DURING_EXECUTION )
			{
				Console::EventNotify("Exception fired during execution. No native Lua error code generated."); 
				return E_FAIL;
			}

			Console::EventNotify(script->GetLastError()); 
		}

		return S_OK;
	}


private:

	IComponentLoaderPtr loader_;

};

int main(int argc, char* const* argv)
{	
	try
	{
		CommandLineHolder< LuaEnvCmd > cmd(argc, argv);

		LuaEnv application;
		application.Process();
	} 
	catch ( CommandLineException& ) 
	{
		LuaEnvCmd::TypeUsage();
	}
	catch ( exception& ex )
	{
		Console::EventNotify("Abnormal program termination caused by the following reason:");
		Console::EventNotify(ex.what());
	}
	catch ( ... )
	{
		Console::EventNotify("Abnormal program termination caused by unknown reason.");
	}

#if defined(_MSC_VER) && defined (_DEBUG)
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}


