#pragma once

#include "..\LuaEngine\LuaApiMacro.h"

#include "GlobalStorage.h"

#include "DataProcessing\DataProcessor.h"
#include "NetworkProcessing\NetworkProcessor.h"
#include "GlobalEnvironment\GlobalApi.h"
#include "SignalsProcessing\SignalsProcessor.h"

// Lua Extension APIs
static const luaL_reg neuroapi_lualibs[] = 
{
	{"data_processing", luaopen_dataprocessing},
	{"network_processing", luaopen_network},
	{"global_environment", luaopen_globalenvironment},
	{"signals_processing", luaopen_signalsprocessing},
	{NULL, NULL}
};