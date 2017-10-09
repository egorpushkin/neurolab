#include "CommonFactory.h"

#include "../TrainersManager/TrainersManager.h"
#include "../Loaders/DirectoryLoader.h"

extern ulong lockCount;
extern ulong objCount;

CCommonFactory::CCommonFactory()
{
	objCount++;
}

CCommonFactory::~CCommonFactory()
{
	lockCount--;
}

// ICommonFactory implementations section	
result CCommonFactory::LockServer(bool Lock)
{
	if(Lock)
		++lockCount;
	else
		--lockCount;

	return S_OK;
}

result CCommonFactory::CreateInstance(ICommon* pObjOuter, REFIID iid, void** ppObject)
{
	if(pObjOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	if (iid == TrMngKit::IID_ITrainersManager)
	{
		TrainersManager* pTrainersManager = new TrainersManager;

		// Ask car for an interface.
		result resultCode = pTrainersManager->QueryInterface(iid, ppObject);

		// Problem?  We must delete the memory we allocated.
		if (FAILED(resultCode) || !(*ppObject))
			delete pTrainersManager;

		return resultCode; // S_OK or E_NOINTERFACE.*/
	
	} else if (iid == TrMngKit::IID_ITrainersLoader)
	{
		DirectoryLoader* pDirLoader = new DirectoryLoader;

		// Ask car for an interface.
		result resultCode = pDirLoader->QueryInterface(iid, ppObject);

		// Problem?  We must delete the memory we allocated.
		if (FAILED(resultCode) || !(*ppObject))
			delete pDirLoader;

		return resultCode; // S_OK or E_NOINTERFACE.*/
	}

    return CLASS_E_CLASSNOTAVAILABLE;
}

// ICommon implementations section	
String CCommonFactory::GetClassString() const
{
	return _T("CCommonFactory");
}

result CCommonFactory::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_ICommonFactory)
	{
		*ppObject = (ICommonFactory*)this;			
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
