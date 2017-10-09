#ifndef ISCRIPTSMACHINE_H__SCRIPTINGKIT__INCLUDED_
#define ISCRIPTSMACHINE_H__SCRIPTINGKIT__INCLUDED_

namespace ScriptingKit
{

	/**
	 * IScriptsMachine interface. 
	 *
	 * @version 1.0.1
	 */
	interface IScriptsMachine : public MinCOM::ICommon
	{
		
		virtual result CreateScript(IScriptPtr& script, bool managed) = 0;
		
		virtual result CreateDataBus(IDataBusPtr& dataBus) = 0;

	};

	typedef MinCOM::ComPtr< IScriptsMachine > IScriptsMachinePtr;
	typedef MinCOM::ComPtr< IScriptsMachine, false > IScriptsMachineWeak;

	// {76d643e3-8c75-4abe-9b93-8f1192299171} 
	DEFINE_GUID(IID_IScriptsMachine, 
	0x76d643e3, 0x8c75, 0x4abe, 0x9b, 0x93, 0x8f, 0x11, 0x92, 0x29, 0x91, 0x71);

	// {7f5f2190-9c47-4e17-a077-60d1d3461118} 
	DEFINE_GUID(CLSID_ScriptsMachine, 
	0x7f5f2190, 0x9c47, 0x4e17, 0xa0, 0x77, 0x60, 0xd1, 0xd3, 0x46, 0x11, 0x18);

} // namespace ScriptingKit

#endif // !ISCRIPTSMACHINE_H__SCRIPTINGKIT__INCLUDED_
