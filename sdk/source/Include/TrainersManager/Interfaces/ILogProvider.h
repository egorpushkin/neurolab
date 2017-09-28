#ifndef ILOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_
#define ILOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_

/**
* ILogProvider interface. Log processing core support. 
* This interface does not define any members. 
* Derive your own interface to add specific logging functionality.
*
* @version 1.0.1
*/
interface ILogProvider : public MinCOM::ICommon
{

};

typedef MinCOM::ComPtr< ILogProvider > ILogProviderPtr;

#endif // !ILOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_
