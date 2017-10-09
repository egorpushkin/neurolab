#ifndef EXECUTIONSTATELOGIMPL_H__TRAINERSMANAGER__INCLUDED_
#define EXECUTIONSTATELOGIMPL_H__TRAINERSMANAGER__INCLUDED_

/**
* ExecutionStateLogImpl class. Partial IExecutionStateLog implementation.
*
* @version 1.0.1
*/
class ExecutionStateLogImpl 
	: public MinCOM::CommonImpl< IExecutionStateLog > 
{
public:

	ExecutionStateLogImpl()
	{
	}

	virtual ~ExecutionStateLogImpl() 
	{
	}

	// IExecutionStateLog implementations section
	virtual bool IsInfoTypeSupported(InfoType /* type = PercentageInfo*/, REFCLSID /* paramId */ = CLSID_DefaultParam)
	{
		/* if (type == TimingInfo)
			return true; */
		
		return false;
	}

	virtual float GetPercentage() const
	{
		return 0.0f;
	}
	
	virtual result SetupTiming(const StringA& /* timingName */)
	{
		return S_FALSE;
	}

	virtual result GetTimeElapsed(const StringA& /* timingName */, double& /* milliseconds */)
	{
		return S_FALSE;
	}

	virtual result GetTimeElapsed(const StringA& /* timingName */, ulong& /* seconds */)
	{
		return S_FALSE;
	}

	virtual result GetParameterValue(const StringA& /* paramName */, MinCOM::CommonVariant& /* paramVal */) const
	{
		return E_NOTIMPL;
	}

	virtual result GetTimeBetweenYimings(const StringA& /* timing1Name */, const StringA& /* timing2Name */, double& /* milliseconds */)
	{
		return E_NOTIMPL;
	}

	virtual result GetTimeBetweenYimings(const StringA& /* timing1Name */, const StringA& /* timing2Name */, ulong& /* seconds */)
	{
		return E_NOTIMPL;
	}

	// ICommon implementations section	
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< IExecutionStateLog >::GetCommon(); 

		else if (iid == IID_IExecutionStateLog)
			*ppObject = static_cast< IExecutionStateLog* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IExecutionStateLog >::GetCommon()->AddRef();
		return S_OK;
	}
};

#endif // !EXECUTIONSTATELOGIMPL_H__TRAINERSMANAGER__INCLUDED_
