//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IID.h
//	Description: Declaration of common object model identificators.  

#ifndef IID_H__COMMON__INCLUDED_
#define IID_H__COMMON__INCLUDED_

#ifndef _GUIDS_
#define _GUIDS_						CommonKitGuidsDef
#endif // !_GUIDS_

namespace _GUIDS_
{

// {3d24c25d-2c73-4a47-9264-a5d5b1bfdf75} 
DEFINE_GUID(IID_ICommon, 
0x3d24c25d, 0x2c73, 0x4a47, 0x92, 0x64, 0xa5, 0xd5, 0xb1, 0xbf, 0xdf, 0x75);

// {eba35dc4-ef78-49ad-b8f3-eb7673e30813} 
DEFINE_GUID(IID_ANY, 
0xeba35dc4, 0xef78, 0x49ad, 0xb8, 0xf3, 0xeb, 0x76, 0x73, 0xe3, 0x08, 0x13);

// {e9148d40-1092-4249-ac4d-11645cffd695} 
DEFINE_GUID(IID_IEnumerator, 
0xe9148d40, 0x1092, 0x4249, 0xac, 0x4d, 0x11, 0x64, 0x5c, 0xff, 0xd6, 0x95);

// {52cef983-561e-45ec-b1e8-39ec50ef4b74} 
DEFINE_GUID(IID_IContainer, 
0x52cef983, 0x561e, 0x45ec, 0xb1, 0xe8, 0x39, 0xec, 0x50, 0xef, 0x4b, 0x74);

// {08f73b9a-2777-4676-85f2-0236e16cff5a} 
DEFINE_GUID(IID_ICommonFactory, 
0x08f73b9a, 0x2777, 0x4676, 0x85, 0xf2, 0x02, 0x36, 0xe1, 0x6c, 0xff, 0x5a);

}

using namespace _GUIDS_;

#endif // !IID_H__COMMON__INCLUDED_
