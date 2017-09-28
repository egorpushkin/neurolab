// TestScripting01.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <tchar.h>


#ifdef _MSC_VER

#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#endif // _MSC_VER


#include "Scripting/ScriptingKit.h"
using namespace ScriptingKit;


//////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "Lua-5.1.1.lib")

#define LUA_BUILD_AS_DLL
#include <Lua.h>


int ext(lua_State* /* L */) 
{
	std::cout << "From Lua method!!" << std::endl;

	return 0;
}

class SomeExt
	: public ExtensionImpl
{
public:

	// IExtension implementations section		
	virtual result EnhanceState(IScriptRef /* script */, lua_State* pState, const ScriptingKit::IDataBusPtr& /* dataBus */)
	{ 
		lua_register(pState, "ext", ext);

		return S_FALSE; 
	}

};
//////////////////////////////////////////////////////////////////////////


int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
	
	{

		ComponentsKit::IComponentLoader* piLoader = CConstructTool<ComponentsKit::CComponentLoader, ComponentsKit::IComponentLoader>
			::ConstructObject(ComponentsKit::IID_IComponentLoader);
		assert(piLoader != NULL);

		piLoader->SetLibraryName(StringA("./ScriptsMachine") + SO_LIB_EXT);
		result resultCode = piLoader->InitializeComponentInstance(CLSID_ScriptsFactory);
		assert(resultCode == S_OK);

		{

			IScriptsMachinePtr machine;
			resultCode = piLoader->QueryComponentObject(IID_IScriptsMachine, (void**)&GetImplRef(machine));
			assert(resultCode == S_OK);

			IScriptPtr script = NULL;
			resultCode = machine->CreateScript(script, false);
			assert(resultCode == S_OK);

			//////////////////////////////////////////////////////////////////////////
			{				
				/*
				IExtensionPtr someExt(new SomeExt, IID_IExtension);
			
				IExtensionsMngPtr extMng(script, IID_IExtensionsMng);
				extMng->Register(someExt);
				*/
			}
			//////////////////////////////////////////////////////////////////////////

			/*
			resultCode = script->LoadFile("test.lua", false);
			if ( FAILED(resultCode) )
			{
				std::cout << "Compilation error:" << std::endl;
				std::cout << script->GetLastError() << std::endl;
			}

			resultCode = script->Execute();
			if ( FAILED(resultCode) )
			{
				std::cout << "Execution error:" << std::endl;
				std::cout << script->GetLastError() << std::endl;
			}
			*/

			resultCode = script->LoadFile("test.lua", true);
			if ( FAILED(resultCode) )
			{
				if ( resultCode == SCR_E_COMPILATION )
					std::cout << "Compilation error:" << std::endl;
				else if ( resultCode == SCR_E_EXECUTION )
					std::cout << "Execution error:" << std::endl;
				else if ( resultCode == SCR_E_EXCEPTION_DURING_EXECUTION )
					std::cout << "Exception fired. No native error code generated." << std::endl;

				std::cout << script->GetLastError() << std::endl;
			}

		}

		piLoader->Release();

	}




#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif // _MSC_VER


	return 0;
}

