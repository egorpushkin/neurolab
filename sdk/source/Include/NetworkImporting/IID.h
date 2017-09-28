//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IID.h
//	Description: Declaration of interface identificators.  

#ifndef IID_H__NETWORKIMPORTING__INCLUDED_
#define IID_H__NETWORKIMPORTING__INCLUDED_

//
// Declaring GUIDs namespace name if it was not specified by the host source
//

#ifndef _GUIDS_
#define _GUIDS_						NetworkImportingKitGuidsDef
#endif // !_GUIDS_

namespace _GUIDS_
{

// {0014316d-832b-48b6-a726-6a71384ef38e} 
DEFINE_GUID(IID_IElement, 
0x0014316d, 0x832b, 0x48b6, 0xa7, 0x26, 0x6a, 0x71, 0x38, 0x4e, 0xf3, 0x8e);

// {b27a54d9-89da-4351-a4bf-8ab440957a0e} 
DEFINE_GUID(IID_IDataFlow, 
0xb27a54d9, 0x89da, 0x4351, 0xa4, 0xbf, 0x8a, 0xb4, 0x40, 0x95, 0x7a, 0x0e);

// {eef58e25-68ca-465d-9900-2fefebaf2603} 
DEFINE_GUID(IID_IDataConnector, 
0xeef58e25, 0x68ca, 0x465d, 0x99, 0x00, 0x2f, 0xef, 0xeb, 0xaf, 0x26, 0x03);

// {89804c5d-456e-4a47-b774-725f6764ea3c} 
DEFINE_GUID(IID_IConnectionsFactory, 
0x89804c5d, 0x456e, 0x4a47, 0xb7, 0x74, 0x72, 0x5f, 0x67, 0x64, 0xea, 0x3c);

// {4d2b46d9-b11c-4019-ab5d-ff11832672ac} 
DEFINE_GUID(IID_ILayerControl, 
0x4d2b46d9, 0xb11c, 0x4019, 0xab, 0x5d, 0xff, 0x11, 0x83, 0x26, 0x72, 0xac);

// {830e9ece-8f43-41d3-81f8-9baa2f20854e} 
DEFINE_GUID(IID_IImportManager, 
0x830e9ece, 0x8f43, 0x41d3, 0x81, 0xf8, 0x9b, 0xaa, 0x2f, 0x20, 0x85, 0x4e);

// {ddd4deae-bdfd-41dc-8021-75c7cbcb77a4} 
DEFINE_GUID(IID_IElementsCollection, 
0xddd4deae, 0xbdfd, 0x41dc, 0x80, 0x21, 0x75, 0xc7, 0xcb, 0xcb, 0x77, 0xa4);

// {25eef258-8278-4d41-b43c-b8b83f867926} 
DEFINE_GUID(IID_INetworkProcessor, 
0x25eef258, 0x8278, 0x4d41, 0xb4, 0x3c, 0xb8, 0xb8, 0x3f, 0x86, 0x79, 0x26);

// {394a3229-476e-4192-9924-90e368f7e349} 
DEFINE_GUID(IID_IStructureBuilder, 
0x394a3229, 0x476e, 0x4192, 0x99, 0x24, 0x90, 0xe3, 0x68, 0xf7, 0xe3, 0x49);

}

using namespace _GUIDS_;

#endif // !IID_H__NETWORKIMPORTING__INCLUDED_
