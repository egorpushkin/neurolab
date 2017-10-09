#ifndef GUID_H__MINCOM__COMMONKIT__INCLUDED_
#define GUID_H__MINCOM__COMMONKIT__INCLUDED_

// Structure which contains Globally Unique Identifier (GUID)
#ifndef GUID_DEFINED
#define GUID_DEFINED
#define __mc__GUID_DEFINED
typedef struct
{
	unsigned long					Data1;
	unsigned short					Data2;
	unsigned short					Data3;
	unsigned char					Data4[8];
} GUID, IID, CLSID;
#define _GUID GUID
#endif // !GUID_DEFINED

// Some macros for operating with GUID objects
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
typedef const GUID &				REFGUID;
#endif // !_REFGUID_DEFINED

#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
typedef const GUID &				REFIID;
#endif // !_REFIID_DEFINED

#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
typedef const GUID &				REFCLSID;
#endif // !_REFCLSID_DEFINED

// GUID operators
#ifndef _SYS_GUID_OPERATORS_
#define _SYS_GUID_OPERATORS_

	#ifndef IsEqualIID

		#define __mc__GUID_OPERATORS_DEFINED

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

#ifdef DEFINE_GUID
#undef DEFINE_GUID
#endif // !DEFINE_GUID

#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)			\
	const GUID name																\
		= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#endif // !GUID_H__MINCOM__COMMONKIT__INCLUDED_
