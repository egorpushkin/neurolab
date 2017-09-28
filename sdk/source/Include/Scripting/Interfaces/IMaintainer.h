#ifndef IMAINTAINER_H__SCRIPTINGKIT__INCLUDED_
#define IMAINTAINER_H__SCRIPTINGKIT__INCLUDED_

namespace ScriptingKit
{

	/**
	 * IMaintainer interface. 
	 *
	 * @version 1.0.1
	 */
	interface IMaintainer : public MinCOM::ICommon
	{

		virtual result Lock() = 0;

		virtual result Unlock() = 0;

		virtual uint GetScriptsCount() = 0;

		virtual IScriptPtr GetScriptAt(uint scriptIndex) = 0;

		virtual result RegisterScript(const IScriptPtr& script) = 0;

		virtual result UnregisterScript(const IScriptPtr& script) = 0;	

	};

	typedef MinCOM::ComPtr< IMaintainer > IMaintainerPtr;

	// {ba863f6f-bfbf-47d3-809a-8d3a2c83285b} 
	DEFINE_GUID(IID_IMaintainer, 
	0xba863f6f, 0xbfbf, 0x47d3, 0x80, 0x9a, 0x8d, 0x3a, 0x2c, 0x83, 0x28, 0x5b);

} // namespace ScriptingKit

#endif // !IMAINTAINER_H__SCRIPTINGKIT__INCLUDED_
