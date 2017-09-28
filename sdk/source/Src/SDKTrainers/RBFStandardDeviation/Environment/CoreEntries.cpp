#include "TrainerMain.h"

#include "CoreEntries.h"

#include "CommonFactory.h"

ulong lockCount = 0;
ulong objCount = 0;

result DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppObject)
{
	if (clsid != TrMngKit::CLSID_Trainer)
		return CLASS_E_CLASSNOTAVAILABLE;

	// They want a CObjectFactory.
	Trainer::CommonFactory* pCommonFactory = new Trainer::CommonFactory;

	// Go get the interface from the CObjectsFactory. 
	result resultCode = pCommonFactory->QueryInterface(iid, ppObject);

	if(FAILED(resultCode) || !(*ppObject)) 
		delete pCommonFactory;

	return resultCode; // S_OK or E_NOINTERFACE.
}

result CanUnloadNow()
{
	if(lockCount != 0 || objCount != 0)
		return S_FALSE;

	return S_OK;
}

void GetComponentName(String& componentName)
{
	componentName = _T("TrainerImplementation");
}

void GetComponentVersion(String& componentVersion)
{
	componentVersion = _T("1.1.0.1");
}
