#pragma once

#ifdef DLL_CONNECT
#define DLL_FUNC_DECLARE __declspec(dllexport)
#else
#define DLL_FUNC_DECLARE __declspec(dllimport)
#endif

//#include <uxtheme.h>
//#include <tmschema.h>

#include <gdiplus.h>
using namespace Gdiplus;

DLL_FUNC_DECLARE void InitializeGDIP();
DLL_FUNC_DECLARE void ReleaseGDIP();

#include <gl/gl.h>	
#include <gl/glu.h>	
#include <gl/glaux.h>

#include "Devices\MemDC.h"
#include "Devices\GDIPDevice.h"
#include "Devices\DeviceDriver.h"
#include "Devices\DeviceFont.h"
#include "Devices\OutputDevice.h"