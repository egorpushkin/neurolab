#pragma once

#include "CmnPlugin.h"

#define DLL_FUNC_DECLARE extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE IPluginControl*		CreatePluginInstance();
DLL_FUNC_DECLARE void					ReleasePluginInstance(IPluginControl* pPlugin);

DLL_FUNC_DECLARE void					GetPluginInfo(PLUGIN_INFO* pInfoStruct);