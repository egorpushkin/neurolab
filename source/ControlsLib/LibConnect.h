#pragma once

#ifdef DLL_CONNECT
#define DLL_FUNC_DECLARE __declspec(dllexport)
#else
#define DLL_FUNC_DECLARE __declspec(dllimport)
#endif

#include "UIControls/DataImageCtrl/DataImageCtrl.h"
#include "UIControls/FuncShowCtrl/FuncShowCtrl.h"
#include "UIControls/ChartingCtrl/Panel/ChartPanelCtrl.h"
