#include "../Common/ScriptsMachine.h"

#include "CommonFactory.h"

#include "../Factory/Factory.h"

namespace ScriptsMachine
{

extern ulong lockCount;
extern ulong objCount;

CommonFactory::CommonFactory()
{
	objCount++;
}

CommonFactory::~CommonFactory()
{
	lockCount--;
}

// ICommonFactory implementations section	
result CommonFactory::LockServer(bool Lock)
{
	if(Lock)
		++lockCount;
	else
		--lockCount;

	return S_OK;
}

result CommonFactory::CreateInstance(ICommon* pObjOuter, REFIID iid, void** ppObject)
{
	if(pObjOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	try
	{
		return ScriptsMachine::CreateObject(ScriptingKit::CLSID_ScriptsMachine)->QueryInterface(iid, ppObject);
	} 
	catch (...)
	{
		return E_NOINTERFACE;
	}	
}

// ICommon implementations section	
result CommonFactory::QueryInterface(REFIID iid, void** ppObject)
{
	if (iid == MinCOM::IID_ICommon)
		*ppObject = MinCOM::CommonImpl< ICommonFactory >::GetCommon();

	else if (iid == MinCOM::IID_ICommonFactory)
		*ppObject = static_cast< MinCOM::ICommonFactory* >(this);

	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	MinCOM::CommonImpl< ICommonFactory >::GetCommon()->AddRef();
	return S_OK;	
}

}
