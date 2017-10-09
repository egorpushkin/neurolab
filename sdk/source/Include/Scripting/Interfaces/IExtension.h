#ifndef IEXTENSION_H__SCRIPTINGKIT__INCLUDED_
#define IEXTENSION_H__SCRIPTINGKIT__INCLUDED_

/**
 * @file IExtension.h
 * @short The IExtension control interface definition. 
 * @author Egor Pushkin <egor.pushkin@scientific-soft.com>
 */

/**
 * @short Preliminary lua_State definition.  
 *
 * This statement made to avoid including Lua headers here.
 */
struct lua_State;

namespace ScriptingKit
{

	/**
	 * @short The IExtension control interface.  
	 *
	 * This control interface must be implemented by the object which purpose is to 
	 * enhance Lua state with custom APIs, constants and other stuff.
	 *
	 * This interface has no common default implementation in scripting engine 
	 * (except partial implementation provided by ExtensionImpl and 
	 * specific implementations). That is why there is no class identifier declared here.
	 *
	 * @version 1.0.1
	 */
	interface IExtension : public MinCOM::ICommon
	{
		
		/**
		 * Performs specific state and data bus initialization before script execution.
		 * 
		 * @param pState State to be enhanced.
		 * @param dataBus Data source. May be NULL.
		 * @return Returns S_OK if successful, or an error value otherwise. 
 		 */
		virtual result EnhanceState(IScriptRef script, lua_State* L, IDataBusRef dataBus) = 0;

	};

	/**
 	 * Strong pointer for the IExtension control interface. 
	 */
	typedef MinCOM::ComPtr< IExtension > IExtensionPtr;

	/**
	 * The IExtension unique identifier. 
	 */
	// {832bb361-45ae-4866-8e72-520d47cef7d7} 
	DEFINE_GUID(IID_IExtension, 
	0x832bb361, 0x45ae, 0x4866, 0x8e, 0x72, 0x52, 0x0d, 0x47, 0xce, 0xf7, 0xd7);

} // namespace ScriptingKit

#endif // !IEXTENSION_H__SCRIPTINGKIT__INCLUDED_
