//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: String.h
//	Description: Common strings macros and definitions.  

#ifndef STRING_H__COMMON__INCLUDED_
#define STRING_H__COMMON__INCLUDED_

/************************************************************************

	Code notes:
		_T(x)	macro must be used to define any string expressions in the code.
		TCHAR	type must be used to declare character variables.			
		String	container must be used to operate with string data.

************************************************************************/

#ifdef _T
#undef _T
#endif // _T

#ifdef _TCHAR_DEFINED
#undef _TCHAR_DEFINED
#endif // _TCHAR_DEFINED

#ifdef _UNICODE
//////////////////////////////////////////////////////////////////////////
// Declaring macros for Unicode mode /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifndef _T
#define _T(x)						L ## x
#endif

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED

typedef wchar_t						TCHAR;

#endif // !__TCHAR_DEFINED

#else // _UNICODE
//////////////////////////////////////////////////////////////////////////
// Declaring macros for MiltiByte mode ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifndef _T
#define _T(x)						x
#endif

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED

typedef char						TCHAR;

#endif // !__TCHAR_DEFINED

#endif // _UNICODE

#ifndef _WINNT_
// Declaring aditional string types
typedef TCHAR*						LPTSTR;
typedef const TCHAR*				LPCTSTR;

// ANSI string macros
typedef char*						LPSTR;
typedef const char*					LPCSTR;
#endif // !_WINNT_

// Declaring object model main string container
typedef basic_string<TCHAR, char_traits<TCHAR>, allocator<TCHAR> >			String;
typedef basic_string< char, char_traits<char>, allocator<char> >			StringA;
typedef basic_string< wchar_t, char_traits<wchar_t>, allocator<wchar_t> >	StringU;

#endif // !STRING_H__COMMON__INCLUDED_
