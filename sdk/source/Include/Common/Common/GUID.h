//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: GUID.h
//	Description: Object model basics. GUID tools and marcos declarations.  

#ifndef GUID_H__COMMON__INCLUDED_
#define GUID_H__COMMON__INCLUDED_

// Structure which contains Globally Unique Identifier (GUID)
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
	unsigned long					Data1;
	unsigned short					Data2;
	unsigned short					Data3;
	unsigned char					Data4[8];
} GUID, IID, CLSID, *LPCLSID;
#endif // !GUID_DEFINED

// Some macros for operating with GUID objects
#ifndef REFGUID
#define REFGUID						const GUID &
#endif // !REFGUID

#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID						const GUID &
#endif // !_REFIID_DEFINED

#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID					const GUID &
#endif // !_REFCLSID_DEFINED

// GUID operators
#if !defined (_SYS_GUID_OPERATORS_)
#define _SYS_GUID_OPERATORS_

	#if !defined (IsEqualIID)

		__inline int IsEqualGUID(REFGUID rGuid1, REFGUID rGuid2)
		{
			return !memcmp(&rGuid1, &rGuid2, sizeof(GUID));
		}

		__inline int operator==(REFGUID rGuid1, REFGUID rGuid2)
		{
			return IsEqualGUID(rGuid1, rGuid2);
		}

		__inline int operator!=(REFGUID rGuid1, REFGUID rGuid2)
		{
			return !(rGuid1 == rGuid2);
		}

		#define IsEqualIID(rGuid1, rGuid2) IsEqualGUID(rGuid1, rGuid2)
		#define IsEqualCLSID(rClsid1, rClsid2) IsEqualGUID(rClsid1, rClsid2)

	#endif  // !IsEqualIID

#endif  // !_SYS_GUID_OPERATORS_

// GUID structure declaration macro
#ifdef DEFINE_GUID
#undef DEFINE_GUID
#endif // !DEFINE_GUID

#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)			\
	const GUID name																\
	= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#endif // !GUID_H__COMMON__INCLUDED_
