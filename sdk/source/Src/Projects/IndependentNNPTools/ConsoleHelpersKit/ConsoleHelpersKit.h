//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: ConsoleHelpersKit.h
//	Description: Console Helpers Kit main file.  

//	Include this file in your solution to add functionality of this Kit.

#ifndef CONSOLEHELPERSKIT_H__CONSOLEHELPERSKIT__INCLUDED_
#define CONSOLEHELPERSKIT_H__CONSOLEHELPERSKIT__INCLUDED_

// Including functionality of NetworkImporting and StoragePtocessor SDK
#ifndef _GUIDS_
#define _GUIDS_ ConsoleHelpersGuidsDef
#endif // !_GUIDS_

#include "NetworkImporting/NetworkImportingKit.h"

// Old versions compatibility trick
namespace MinCOM
{	
	using namespace CommonKit;
}

// Smart objects containing and enumeration
#include "Common/ContainerNew/Container.h"

#include "../StorageProcessor/Common/Common.h"
#include "TrainersManager/TrainersManagerKit.h"

// getopt routines 
#include "getopt/getoptinclude.h"

namespace ConsoleHelpersKit
{
	#include "Exceptions.h"
	#include "Console.h"
	#include "CommandLine.h"

	#include "Application.h"

	#include "Helpers/NetworkImportHelper.h"
	#include "Helpers/StorageProcessorHelper.h"
	#include "Helpers/ConfigHelper.h"
	#include "Helpers/TrainersManagerHelper.h"
}

// Debug interface for MSVC
#ifdef _MSC_VER
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

// Required constants and definitions for ported code 
#ifndef MAX_PATH
const uint MAX_PATH = 255;
#endif // !MAX_PATH

#endif // !CONSOLEHELPERSKIT_H__CONSOLEHELPERSKIT__INCLUDED_

