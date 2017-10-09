//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CmnComponentsLib.h
//	Description: Common Components library declarations.

#ifndef CMNCOMPONENTSLIB_H__COMPONENTSLIB__INCLUDED_
#define CMNCOMPONENTSLIB_H__COMPONENTSLIB__INCLUDED_

// 
// Declaring library macros
// 

#define _LIBRARY_IMPLEMENTATION_
#define _COMPONENTS_LIBRARY_IMPLEMENTATION_

//
// Including required system headers for shared objects management
//

#ifdef WIN32
#include "windows.h"
#else // WIN32
#include <dlfcn.h>
#endif // WIN32

// Including Data Processing SDK headers
#define _GUIDS_						ComponentsLibGuidsDef
#include "Components/ComponentsKit.h"

#endif // !CMNCOMPONENTSLIB_H__COMPONENTSLIB__INCLUDED_
