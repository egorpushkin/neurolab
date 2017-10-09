#pragma once

#ifdef DLL_CONNECT
#define DLL_FUNC_DECLARE __declspec(dllexport)
#else
#define DLL_FUNC_DECLARE __declspec(dllimport)
#endif

#include <gdiplus.h>

#include "UIControls/DataImageCtrl.h"
#include "UIControls/DisplayPGMCtrl.h"

void InitializeGDIP();
void ReleaseGDIP();

