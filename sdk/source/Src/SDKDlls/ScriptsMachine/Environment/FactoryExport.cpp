#include "../Common/ScriptsMachine.h"

#include "../Factory/Factory.h"

namespace ScriptsMachine
{

extern ulong lockCount;
extern ulong objCount;

EXPORT_SYMBOL_SIGNATURE result CreateObject(REFCLSID clsid, MinCOM::ICommonPtr& common)
{
	try
	{		
		return ((common = ScriptsMachine::CreateObject(clsid)) != NULL) ? S_OK : NULL;
	} 
	catch (...)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}	
}

EXPORT_SYMBOL_SIGNATURE result LockLibrary(bool lock)
{
	if(lock)
		++lockCount;
	else
		--lockCount;

	return S_OK;	
}

EXPORT_SYMBOL_SIGNATURE result CanUnloadNow()
{
	if(lockCount != 0 || objCount != 0)
		return S_FALSE;

	return S_OK;
}

}
