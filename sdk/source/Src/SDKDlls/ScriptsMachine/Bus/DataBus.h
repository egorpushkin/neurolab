#ifndef DATABUS_H__SCRIPTSMACHINE__INCLUDED_
#define DATABUS_H__SCRIPTSMACHINE__INCLUDED_

namespace ScriptsMachine
{

class DataBus
	: public MinCOM::CommonImpl< ScriptingKit::IDataBus >
{

	BEGIN_LOCAL_QI_MAP()
		DECLARE_COMMON(ScriptingKit::IDataBus)
		DECLARE_IID(ScriptingKit::IDataBus, ScriptingKit::IID_IDataBus)
	END_LOCAL_QI_MAP()

public:
	DataBus();
	virtual ~DataBus();

	// IDataBus declarations section	
	virtual result AcquireData(const StringA& name, const ICommonPtr& data);
	virtual result ReleaseData(const StringA& name);
	virtual bool IsAcquired(const StringA& name);
	virtual result Refresh();
	virtual ICommonPtr GetData(const StringA& name);        

	// ICommon declarations section	
	virtual result QueryInterface(REFIID iid, void** ppObject);

private:

};

}

#endif // !DATABUS_H__SCRIPTSMACHINE__INCLUDED_
