#ifndef SCRIPTSMACHINE_H__SCRIPTSMACHINE__INCLUDED_
#define SCRIPTSMACHINE_H__SCRIPTSMACHINE__INCLUDED_

// GNU Common C++ engine
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4127) // conditional expression is constant
#endif

//#define DONOT_INCLUDE_WINSOCK2	// Custom workaround for win32 custom include
// compatibility troubles
#define DONOT_DEFINE_UINT	// Custom workaround for uint duplicate definition
#define CCXX_STATIC			// cc++ standard feature
#include <cc++/thread.h>

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

// Lua 
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// External includes
#include "Components/ComponentsKit.h"
#include "Scripting/ScriptingKit.h"

// Internal includes
#include "../Extensions/Macros.h"




#endif // !SCRIPTSMACHINE_H__SCRIPTSMACHINE__INCLUDED_
