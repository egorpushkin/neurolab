//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IID.h
//	Description: Declaration of interface identificators.  

#ifndef IID_H__DATAPROCESSING__INCLUDED_
#define IID_H__DATAPROCESSING__INCLUDED_

//
// Declaring GUIDs namespace name if it was not specified by the host source
//

#ifndef _GUIDS_
#define _GUIDS_						DataProcessingGuidsDef
#endif // !_GUIDS_

namespace _GUIDS_
{

//
// Storage controllers
//

// {1bce0114-e5ba-46e5-a9b8-65d74b7c5112} 
DEFINE_GUID(IID_IStorageController, 
0x1bce0114, 0xe5ba, 0x46e5, 0xa9, 0xb8, 0x65, 0xd7, 0x4b, 0x7c, 0x51, 0x12);

// {f6a6630e-390e-4122-b87e-cc80d5fb0e53} 
DEFINE_GUID(IID_XMLStorageontroller, 
0xf6a6630e, 0x390e, 0x4122, 0xb8, 0x7e, 0xcc, 0x80, 0xd5, 0xfb, 0x0e, 0x53);

//
// Data objects
//

// {fe1276b1-a284-49d1-8fae-aa0e038d318c} 
DEFINE_GUID(IID_IDataFactory, 
0xfe1276b1, 0xa284, 0x49d1, 0x8f, 0xae, 0xaa, 0x0e, 0x03, 0x8d, 0x31, 0x8c);

// {859a29b3-61ba-4627-8d6f-5a45ab591f45} 
DEFINE_GUID(IID_IPGMFactory, 
0x859a29b3, 0x61ba, 0x4627, 0x8d, 0x6f, 0x5a, 0x45, 0xab, 0x59, 0x1f, 0x45);

// {6efc6ac1-d367-4853-8879-a225f984fb30} 
DEFINE_GUID(IID_IBMPFactory, 
0x6efc6ac1, 0xd367, 0x4853, 0x88, 0x79, 0xa2, 0x25, 0xf9, 0x84, 0xfb, 0x30);

// {d597b4b6-14fd-4451-9481-e724b46949fc} 
DEFINE_GUID(IID_IDataFile, 
0xd597b4b6, 0x14fd, 0x4451, 0x94, 0x81, 0xe7, 0x24, 0xb4, 0x69, 0x49, 0xfc);

// {989a83ee-3cb5-4bb8-a096-3c7c0ecc5e85} 
DEFINE_GUID(IID_IDataBitmap, 
0x989a83ee, 0x3cb5, 0x4bb8, 0xa0, 0x96, 0x3c, 0x7c, 0x0e, 0xcc, 0x5e, 0x85);

// {eaa5f3d7-6df6-4e5b-a539-9c8886cdb6a8} 
DEFINE_GUID(IID_IPGMBitmap, 
0xeaa5f3d7, 0x6df6, 0x4e5b, 0xa5, 0x39, 0x9c, 0x88, 0x86, 0xcd, 0xb6, 0xa8);

}

using namespace _GUIDS_;

#endif // !IID_H__DATAPROCESSING__INCLUDED_
