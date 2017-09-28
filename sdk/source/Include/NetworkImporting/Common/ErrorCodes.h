//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ErrorCodes.h
//	Description: Error codes mechanizm implementation.  

#ifndef ERRORCODES_H__NETWORKIMPORTING__INCLUDED_
#define ERRORCODES_H__NETWORKIMPORTING__INCLUDED_

//
// Define the facility code for Network Importing SDK errors
// 

#define FACILITY_NI_SDK				0x40

//
// Define network importing and processing error codes
//

// Transfer functions operations
#define NI_E_FUNCTIONNOTFOUND		((result)0x80400001L)

// Network construction errors
#define NI_E_CANNOTCONNECT			((result)0x80400101L)


#endif // !ERRORCODES_H__NETWORKIMPORTING__INCLUDED_
