//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CLSID.h
//	Description: Declaration of network importing object model identificators.  

#ifndef CLSID_H__NETWORKIMPORTING__INCLUDED_
#define CLSID_H__NETWORKIMPORTING__INCLUDED_

//
// Declaring GUIDs namespace name if it was not specified by the host source
//

#ifndef _GUIDS_
#define _GUIDS_						NetworkImportingKitGuidsDef
#endif // !_GUIDS_

namespace _GUIDS_
{

// {c259695b-fda4-4e73-9121-63f259d961f9} 
DEFINE_GUID(CLSID_NetworkImport, 
0xc259695b, 0xfda4, 0x4e73, 0x91, 0x21, 0x63, 0xf2, 0x59, 0xd9, 0x61, 0xf9);

}

using namespace _GUIDS_;

#endif // !CLSID_H__NETWORKIMPORTING__INCLUDED_
