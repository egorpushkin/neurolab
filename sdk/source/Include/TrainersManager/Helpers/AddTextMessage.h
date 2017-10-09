#ifndef ADDTEXTMESSAGE_H__TRAINERSMANAGER__INCLUDED_
#define ADDTEXTMESSAGE_H__TRAINERSMANAGER__INCLUDED_

inline result AddTextMessage(
	ITrainer* piTrainer, 
	const StringA& type, const StringA& message, const StringA& section)
{
	ILogProvider* piLog = piTrainer->GetLogProvider();
	if (!piLog)
		return S_FALSE;
	
	ITextLogProvider* piTextLog = NULL;	
	piLog->QueryInterface(IID_ITextLogProvider, (void**)&piTextLog);
	if (!piTextLog)
	{
		piLog->Release();
		return S_FALSE;
	}

	piTextLog->AddMessage(type, message, section);
	
	piTextLog->Release();
	piLog->Release();
    
	return S_OK;
}

inline result AddTextMessage(
	ITrainerRef trainer,
	const StringA& type, const StringA& message, const StringA& section)
{
	return AddTextMessage(GetImpl((ITrainerPtr)trainer), type, message, section);
}

#endif // !ADDTEXTMESSAGE_H__TRAINERSMANAGER__INCLUDED_
