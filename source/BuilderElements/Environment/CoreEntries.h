#pragma once

#include "CmnManager.h"

#define DLL_FUNC_DECLARE extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE IManagerControl *		CreateBuilderManager();
DLL_FUNC_DECLARE void					ReleaseBuilderManager(IManagerControl * pManager);

DLL_FUNC_DECLARE CString				GetComponentName();
DLL_FUNC_DECLARE CString				GetComponentVersion();