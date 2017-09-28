#ifndef FACTORY_H__SCRIPTSMACHINE__INCLUDED_
#define FACTORY_H__SCRIPTSMACHINE__INCLUDED_

namespace ScriptsMachine
{

	MinCOM::ICommonPtr CreateObject(REFCLSID clsid);

}

#endif // !FACTORY_H__SCRIPTSMACHINE__INCLUDED_
