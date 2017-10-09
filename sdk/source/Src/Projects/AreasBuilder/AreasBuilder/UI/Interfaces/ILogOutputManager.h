#ifndef ILOGOUTPUTMANAGER_H__PROJECTUI__INCLUDED_
#define ILOGOUTPUTMANAGER_H__PROJECTUI__INCLUDED_

namespace ProjectUI
{

// {d12bbc75-5017-41d8-b3a9-a319c7b7f630} 
DEFINE_GUID(IID_ILogOutputManager, 
0xd12bbc75, 0x5017, 0x41d8, 0xb3, 0xa9, 0xa3, 0x19, 0xc7, 0xb7, 0xf6, 0x30);

interface ILogOutputManager : public ICommon
{
	virtual result			DisplayLogMessage(const String& providerName, const String& message, bool performSwitchToProvider = true) = 0;
	virtual result			ClearLog(const String& providerName, bool performSwitchToProvider = true) = 0;
	virtual result			SwitchToProvider(const String& providerName) = 0;
};

}

#endif // !ILOGOUTPUTMANAGER_H__PROJECTUI__INCLUDED_
