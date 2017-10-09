#include "CoreEntries.h"

#include "CommonFactory.h"

ulong lockCount = 0;
ulong objCount = 0;

result DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppObject)
{
	if (clsid != TrMngKit::CLSID_TrainersManager)
		return CLASS_E_CLASSNOTAVAILABLE;

	// They want a CObjectFactory.
	CCommonFactory* pCommonFactory = new CCommonFactory;

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

void GetComponentName(String& rComponentName)
{
	rComponentName = _T("TrainersManager");
}

void GetComponentVersion(String& rComponentVersion)
{
	rComponentVersion = _T("1.1.0.1");
}
