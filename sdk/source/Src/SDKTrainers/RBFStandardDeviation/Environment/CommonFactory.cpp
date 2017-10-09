#include "TrainerMain.h"

#include "CommonFactory.h"

#include "../Trainer/Trainer.h"

extern ulong lockCount;
extern ulong objCount;

namespace Trainer
{

CommonFactory::CommonFactory()
{
	++objCount;
}

CommonFactory::~CommonFactory()
{
	--lockCount;
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

	if (iid == TrMngKit::IID_ITrainer)
	{
		Trainer* pTrainer = new Trainer;

		// Ask car for an interface.
		result resultCode = pTrainer->QueryInterface(iid, ppObject);

		// Problem?  We must delete the memory we allocated.
		if (FAILED(resultCode) || !(*ppObject))
			delete pTrainer;

		return resultCode; // S_OK or E_NOINTERFACE.	
	}

    return CLASS_E_CLASSNOTAVAILABLE;
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

} // namespace Trainer
