//	This code is a part of Common SDK.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Common.h
//	Description: Common SDK declarations.   

#ifndef COMMON_H__COMMON__INCLUDED_
#define COMMON_H__COMMON__INCLUDED_

// Common includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <io.h>

// External C++ Toolkits
// Loki Library
#include "../../../ExternalEngines/Include/Loki/AssocVector.h"
#include "../../../ExternalEngines/Include/Loki/Singleton.h"
#include "../../../ExternalEngines/Include/Loki/SmartPtr.h"

// Common SDK configuration
//////////////////////////////////////////////////////////////////////////
// Unicode section started ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/************************************************************************
	
	The following list of defines are avaliabe in this sextion:
		#define _UNICODE	-	Use it to compile library and inherited 
								code using unicode characters set.

************************************************************************/

// Defines list for unicode section
#ifndef SKIP_FORCED_UNICODE_DECLARATION

#ifndef _UNICODE
#define _UNICODE
#endif // !_UNICODE

#endif // !#SKIP_FORCED_UNICODE_DECLARATION

//#ifdef _UNICODE
#include <wchar.h>
//#endif // !_UNICODE

//////////////////////////////////////////////////////////////////////////
// Unicode section finished //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// Most common syntax declarations
#define interface					struct

// Most common types declarations
typedef unsigned char				byte;
typedef unsigned short				word;
typedef unsigned short				ushort;
typedef unsigned int				uint;
typedef	unsigned int				uint_ptr;
typedef	long						long_ptr;
typedef unsigned long				ulong;
typedef __int64						longlong;
typedef unsigned __int64			ulonglong;
typedef unsigned long				dword;
typedef unsigned long				dword_ptr;
typedef	unsigned long				ulong_ptr;

typedef double date;

typedef void*						pvoid;
typedef void*						handle;

#ifndef _WPARAM_DEFINED
#define _WPARAM_DEFINED
typedef long_ptr					wparam;
#endif // !_WPARAM_DEFINED

#ifndef _LPARAM_DEFINED
#define _LPARAM_DEFINED
typedef long_ptr					lparam;
#endif // !_LPARAM_DEFINED

#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((word)(((byte)((dword_ptr)(a) & 0xff)) | ((word)((byte)((dword_ptr)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((long)(((word)((dword_ptr)(a) & 0xffff)) | ((dword)((word)((dword_ptr)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((word)((dword_ptr)(l) & 0xffff))
#define HIWORD(l)           ((word)((dword_ptr)(l) >> 16))
#define LOBYTE(w)           ((byte)((dword_ptr)(w) & 0xff))
#define HIBYTE(w)           ((byte)((dword_ptr)(w) >> 8))
#endif // !MAKEWORD

#endif // !COMMON_H__COMMON__INCLUDED_
