#ifndef LOGPROVIDER_H__AREASEXTRACTOR__INCLUDED_
#define LOGPROVIDER_H__AREASEXTRACTOR__INCLUDED_

class LogProvider
	: public MinCOM::CommonImpl< TrMngKit::ITextLogProvider >
{
public:

	// ITextLogProvider implementations section	
	virtual result AddMessage(const StringA& type, const StringA& message, const StringA& section)
	{
		ConsoleHelpersKit::Console::EventNotify(
			StringA("Trainer. ")+
			type + 
			StringA(": ")+
			message + 
			StringA(" [ ")+
			section +
			StringA(" ]")
		);

		return S_OK;
	}

	// ITextLogProvider implementations section	

	// ICommon implementations section	
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< TrMngKit::ITextLogProvider >::GetCommon();

		else if (iid == TrMngKit::IID_ILogProvider)
			*ppObject = static_cast< TrMngKit::ILogProvider* >(this);

		else if (iid == TrMngKit::IID_ITextLogProvider)
			*ppObject = static_cast< TrMngKit::ITextLogProvider* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< TrMngKit::ITextLogProvider >::GetCommon()->AddRef();
		return S_OK;	
	}
};

#endif // !LOGPROVIDER_H__AREASEXTRACTOR__INCLUDED_
