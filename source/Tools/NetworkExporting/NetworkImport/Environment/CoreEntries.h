#pragma once

#include "CmnNetworkImport.h"

#define DLL_FUNC_DECLARE extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE IImportManager *		CreateImportManager();
DLL_FUNC_DECLARE void					ReleaseImportManager(IImportManager* pManager);

DLL_FUNC_DECLARE CString				GetComponentName();
DLL_FUNC_DECLARE CString				GetComponentVersion();