#pragma once

#include "CmnExternalElement.h"

#define DLL_FUNC_DECLARE extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE IExternalElementsContainer* CreateExternalManager();
DLL_FUNC_DECLARE void ReleaseExternalManager(IExternalElementsContainer* pContainer);