//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CLSID.h
//	Description: Declaration of interface identificators.  

#ifndef CLSID_H__COMPONENTS__INCLUDED_
#define CLSID_H__COMPONENTS__INCLUDED_

//
// Declaring GUIDs namespace name if it was not specified by the host source
//

#ifndef _GUIDS_
#define _GUIDS_						ComponentsKitGuidsDef
#endif // !_GUIDS_

namespace _GUIDS_
{

// {117a124e-fd58-442f-934b-fe50c176ddcb} 
DEFINE_GUID(CLSID_ComponentsKit, 
0x117a124e, 0xfd58, 0x442f, 0x93, 0x4b, 0xfe, 0x50, 0xc1, 0x76, 0xdd, 0xcb);

}

using namespace _GUIDS_;

#endif // !CLSID_H__COMPONENTS__INCLUDED_
