//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IID.h
//	Description: Declaration of interface identificators.  

#ifndef IID_H__COMPONENTS__INCLUDED_
#define IID_H__COMPONENTS__INCLUDED_

//
// Declaring GUIDs namespace name if it was not specified by the host source
//

#ifndef _GUIDS_
#define _GUIDS_						ComponentsKitGuidsDef
#endif // !_GUIDS_

namespace _GUIDS_
{

// {7d7a0998-eb5b-47cf-a44a-435ff55b7e8f} 
DEFINE_GUID(IID_IComponentLoader, 
0x7d7a0998, 0xeb5b, 0x47cf, 0xa4, 0x4a, 0x43, 0x5f, 0xf5, 0x5b, 0x7e, 0x8f);

}

using namespace _GUIDS_;

#endif // !IID_H__COMPONENTS__INCLUDED_
