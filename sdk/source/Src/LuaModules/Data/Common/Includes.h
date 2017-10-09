#ifndef INCLUDES_H__DATA__INCLUDED_
#define INCLUDES_H__DATA__INCLUDED_

#include <lua.h>
#include <lauxlib.h> 

#include "Common/CommonKit.h"
using namespace CommonKit;

namespace MinCOM
{	
	// Connect symbols declared in CommonKit
	using namespace CommonKit;
}

#include "Common/ContainerNew/Container.h"

#include "DataProcessing/DataProcessingKit.h"

#include "Lua/LuaKit.h"

namespace DpKit = DataProcessingKit;

#include "../Tools/auxiliar.h"

#endif // !INCLUDES_H__DATA__INCLUDED_
