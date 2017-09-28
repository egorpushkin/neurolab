#pragma once

#include "CmnManager.h"

#define DLL_FUNC_DECLARE extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE IManagerControl *		CreateNetworkTrainers();
DLL_FUNC_DECLARE void					ReleaseNetworkTrainers(IManagerControl* pManager);

DLL_FUNC_DECLARE CString				GetComponentName();
DLL_FUNC_DECLARE CString				GetComponentVersion();