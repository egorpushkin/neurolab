//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: SharedObjects.h
//	Description: Common shared objects declarations.

#ifndef SHAREDOBJECTS_H__COMPONENTSLIB__INCLUDED_
#define SHAREDOBJECTS_H__COMPONENTSLIB__INCLUDED_

//
// Common declarations
//

#ifdef WIN32
#define WIN32_PLATFORM
#else // WIN32
#define NOT_WIN32_PLATFORM
#endif // WIN32

//
// Standart definitions for shared object imports and exports declarations
//

#ifdef WIN32_PLATFORM

#define EXPORT_SYMBOL_SIGNATURE extern "C" __declspec(dllexport)
#define IMPORT_SYMBOL_SIGNATURE extern "C" __declspec(dllimport)

#else // WIN32_PLATFORM
// Linux replacements

#define EXPORT_SYMBOL_SIGNATURE extern "C"
#define IMPORT_SYMBOL_SIGNATURE extern "C"

#endif // WIN32_PLATFORM

//
// Standart routines for shared object management syntax replacement declaraion
//

#ifdef WIN32_PLATFORM
// Win32 replacements

#define SD_LoadLibrary(lib_name)										\
			LoadLibraryA(lib_name)

#define SD_GetProcAddress(lib_module, routine_name)						\
			GetProcAddress((HMODULE)lib_module, routine_name);

#define SD_FreeLibrary(lib_module)										\
			FreeLibrary((HMODULE)lib_module)

#define SO_LIB_EXT						StringA(".dll")

#else // WIN32_PLATFORM
// Linux replacements

#define SD_LoadLibrary(lib_name)										\
			dlopen(lib_name, RTLD_LAZY)

#define SD_GetProcAddress(lib_module, routine_name)						\
			dlsym(lib_module, routine_name);

#define SD_FreeLibrary(lib_module)										\
			dlclose(lib_module)

#define SO_LIB_EXT						StringA(".so")

#endif // WIN32_PLATFORM

#endif // !SHAREDOBJECTS_H__COMPONENTSLIB__INCLUDED_
