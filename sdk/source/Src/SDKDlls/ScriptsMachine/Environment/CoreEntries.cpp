#include "../Common/ScriptsMachine.h"

#include "../Factory/Factory.h"

namespace ScriptsMachine
{

ulong lockCount = 0;
ulong objCount = 0;

EXPORT_SYMBOL_SIGNATURE result DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppObject)
{
	try
	{
		return ScriptsMachine::CreateObject(clsid)->QueryInterface(iid, ppObject);
	} 
	catch (...)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

EXPORT_SYMBOL_SIGNATURE void GetComponentName(String& componentName)
{
	componentName = _T("ScriptsMachine");
}

EXPORT_SYMBOL_SIGNATURE void GetComponentVersion(String& componentVersion)
{
	componentVersion = _T("1.0.0.1");
}

}
