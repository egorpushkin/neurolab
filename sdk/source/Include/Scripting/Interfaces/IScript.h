#ifndef ISCRIPT_H__SCRIPTINGKIT__INCLUDED_
#define ISCRIPT_H__SCRIPTINGKIT__INCLUDED_

namespace ScriptingKit
{

	/**
	 * IScript interface. 
	 *
	 * @version 1.0.1
	 */
	interface IScript : public MinCOM::ICommon
	{
        	
		virtual result LoadFile(const StringA& filename, bool execute) = 0;

		virtual result LoadString(const StringA& buffer, bool execute) = 0;

		virtual StringA GetFileName() = 0;

		virtual StringA GetLastError() = 0;

		virtual result GetLastErrorResult() = 0;

		virtual result Execute() = 0;

		virtual bool IsRunning() = 0;

		virtual result AttachBus(const IDataBusPtr& dataBus) = 0;    

		virtual IDataBusPtr GetDataBus() = 0;    

	};

	typedef MinCOM::ComPtr< IScript > IScriptPtr;
	typedef const IScriptPtr& IScriptRef;

	// {75de4b2d-6a0d-4259-b250-edeb9dd8b84e} 
	DEFINE_GUID(IID_IScript, 
	0x75de4b2d, 0x6a0d, 0x4259, 0xb2, 0x50, 0xed, 0xeb, 0x9d, 0xd8, 0xb8, 0x4e);

	// {c01b48f1-2224-4d9b-b51e-7f9131268f03} 
	DEFINE_GUID(CLSID_Script, 
	0xc01b48f1, 0x2224, 0x4d9b, 0xb5, 0x1e, 0x7f, 0x91, 0x31, 0x26, 0x8f, 0x03);

	// {0a96c8ee-a604-475c-8db3-ad0c6af93f83} 
	DEFINE_GUID(CLSID_AdvancedScript, 
	0x0a96c8ee, 0xa604, 0x475c, 0x8d, 0xb3, 0xad, 0x0c, 0x6a, 0xf9, 0x3f, 0x83);

} // namespace ScriptingKit

#endif // !ISCRIPT_H__SCRIPTINGKIT__INCLUDED_
