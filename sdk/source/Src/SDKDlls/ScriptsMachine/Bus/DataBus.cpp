#include "../Common/ScriptsMachine.h"

#include "DataBus.h"

namespace ScriptsMachine
{

extern ulong objCount;

DataBus::DataBus()
{
	++objCount;
}

DataBus::~DataBus()
{
	--objCount;
}

// IDataBus implementations section	
result DataBus::AcquireData(const StringA& /* name */, const ICommonPtr& /* data */)
{
	return E_NOTIMPL;
}

result DataBus::ReleaseData(const StringA& /* name */)
{
	return E_NOTIMPL;
}

bool DataBus::IsAcquired(const StringA& /* name */)
{
	return false;
}

result DataBus::Refresh()
{
	return E_NOTIMPL;
}

ICommonPtr DataBus::GetData(const StringA& /* name */)
{
	return NULL;
}

// ICommon implementations section	
result DataBus::QueryInterface(REFIID iid, void** ppObject)
{
	LOCAL_QI(iid, ppObject);

	*ppObject = NULL;
	return E_NOINTERFACE;
}

}
