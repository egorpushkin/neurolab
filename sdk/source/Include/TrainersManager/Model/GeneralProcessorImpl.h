#ifndef GENERALPROCESSORIMPL_H__TRAINERSMANAGER__INCLUDED_
#define GENERALPROCESSORIMPL_H__TRAINERSMANAGER__INCLUDED_

/**
* GeneralProcessorImpl class. Partial IGeneralProcessor implementation.
*
* @version 1.0.1
*/
class GeneralProcessorImpl 
	: public MinCOM::CommonImpl< IGeneralProcessor > 
{
public:

	GeneralProcessorImpl()
	{
	}

	virtual ~GeneralProcessorImpl() 
	{
	}

	// IGeneralProcessor implementations section

	// Not overridden in this scope
	// virtual result Start() = 0;

	virtual result Suspend()
	{
		return E_NOTIMPL;
	}

	virtual result Resume()	
	{
		return E_NOTIMPL;
	}

	virtual result Stop()
	{
		return E_NOTIMPL;
	}

	// ICommon implementations section	
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< IGeneralProcessor >::GetCommon(); 

		else if (iid == IID_IGeneralProcessor)
			*ppObject = static_cast< IGeneralProcessor* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IGeneralProcessor >::GetCommon()->AddRef();
		return S_OK;
	}
};

#endif // !GENERALPROCESSORIMPL_H__TRAINERSMANAGER__INCLUDED_
