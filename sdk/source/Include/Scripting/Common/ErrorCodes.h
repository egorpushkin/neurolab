#ifndef ERRORCODES_H__SCRIPTINGKIT__INCLUDED_
#define ERRORCODES_H__SCRIPTINGKIT__INCLUDED_

namespace ScriptingKit
{

	/**
	 *
	 * Result bit structure:
	 *
	 * \code
	 * |31         24|23           16|15            8|7             0|
	 * | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 
	 * |s| Reserved  |   Facility    |           Error code          |
	 * \endcode
	 * 
	 * Result fields description:
	 * The facility field indicates the system service responsible 
	 * for the error.	
	 */

	/**
	 * Indicates facility code for scripting engine.
	 */
	const result FACILITY_SCRIPTING				= 0x81;

	/**
	 * Error codes for Scripting Kit enumeration.
	 */
	enum ErrorCodes
	{
		/**
		 * Fires by the object which implements IScript when user attempts to execute 
		 * one and the same script in multi threaded environment more than once.
		 */ 
		SCR_E_ALREADY_EXECUTED					= 0x80810001L,
		
		/**
		 * Fires when attempting to specify wrong or not supported execution method 
		 * for script executor.
		 */ 
		SCR_E_WRONG_EXEC_METHOD,

		/**
		 * Indicates that empty state have not been properly created via lua_open.
		 */ 
		SCR_E_FAILED_TO_CREATE_EMPTY_STATE,

		/**
		 * Indicates that commands for execution have not been not loaded.
		 */ 
		SCR_E_NOTHING_TO_EXECUTE,

		/**
		 * Indicates that error code has not been pushed onto the stack.
		 */ 
		SCR_E_NO_ERROR_CODE_ON_THE_STACK,

		/**
	 	 * Script execution terminated by unknown exception.
	 	 */ 
		SCR_E_EXCEPTION_DURING_EXECUTION,

		/**
		 * Extensions were not installed successfully.
		 */ 
		SCR_E_FAILED_TO_INSTALL_EXTENSIONS,

		/**
		 * Extensions were not uninstalled successfully.
		 */ 
		SCR_E_FAILED_TO_UNINSTALL_EXTENSIONS,

		/**
		* Indicates that Lua function returned unidentified error value.
		 */ 
		SCR_E_LUA_ERRUNKNOWN,

		/**
		 * This is binding code for standard Lua error LUA_ERRSYNTAX.
		 * Original meaning is: syntax error during pre-compilation.
		 */ 
		SCR_E_LUA_ERRSYNTAX,

		/**
		 * This is binding code for standard Lua error LUA_ERRMEM.
		 * Original meaning is: memory allocation error.
		 */ 
		SCR_E_LUA_ERRMEM,

		/**
		 * This is binding code for standard Lua error LUA_ERRRUN.
		 * Original meaning is: a runtime error.
		 */ 
		SCR_E_LUA_ERRRUN,

		/**
	 	 * This is binding code for standard Lua error LUA_ERRRUN.
	 	 * Original meaning is: error while running the error handler function.
		 */ 
		SCR_E_LUA_ERRERR,

		/**
		 * Fires when compilation fails.
		 */ 
		SCR_E_COMPILATION,

		/**
		 * Fires when execution fails.
		 */ 
		SCR_E_EXECUTION,

		/**
		 * Indicates that compiled chunk has been already pushed as a Lua function on top of the stack.
		 */ 
		SCR_E_ALREADY_LOADED,

		/**
		 * Indicates that compiled chunk has not been pushed as a Lua function on top of the stack yet.
		 */ 
		SCR_E_NOT_LOADED


	};

} // namespace ScriptingKit

#endif // !ERRORCODES_H__SCRIPTINGKIT__INCLUDED_
