#ifndef SCRIPTINGKIT_H__SCRIPTINGKIT__INCLUDED_
#define SCRIPTINGKIT_H__SCRIPTINGKIT__INCLUDED_

/**
 * @file ScriptingKit.h
 * @short This is main Scripting Kit include file. 
 * @author Egor Pushkin <egor.pushkin@scientific-soft.com>
 */

#include "ExternalIncludes.h"

/**
 * Primary scripting engine namespace
 */
namespace ScriptingKit
{
} // namespace ScriptingKit

/**
 * Scripting Kit namespace content: 
 *	- Core structures and error codes ();
 *	- Control interfaces;
 *	- Partial implementations.
 */
#include "Common/ExecutionMethod.h"
#include "Common/ErrorCodes.h"

#include "Interfaces/IDataBus.h"
#include "Interfaces/IScript.h"

#include "Interfaces/IExtension.h"
#include "Interfaces/IExtensionsMng.h"

#include "Interfaces/IMaintainer.h"
#include "Interfaces/IScriptsMachine.h"

#include "Identifiers/CLSID.h"

#include "Model/ExtensionImpl.h"	

#include "Exceptions/Core.h"



#endif // !SCRIPTINGKIT_H__SCRIPTINGKIT__INCLUDED_
