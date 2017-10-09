//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ErrorCodes.h
//	Description: Error codes mechanizm implementation.  

#ifndef ERRORCODES_H__COMMON__INCLUDED_
#define ERRORCODES_H__COMMON__INCLUDED_

// Defining base data type for error storage
typedef long						result;

/************************************************************************

	RESULT bit structure:
		
		|31         24|23           16|15            8|7             0|
		| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 
		|s| Reserved  |   Facility    |           Error code          |

	RESULT fields description:
		The facility field indicates the system service responsible 
		for the error.	

************************************************************************/

//
// Define the severity codes
// 

#define SEVERITY_ERROR				1
#define SEVERITY_SUCCESS			0

//
// Define the facility codes
// 

#define FACILITY_STORAGE			3
#define FACILITY_STATE_MANAGEMENT	34
#define FACILITY_SECURITY			9
#define FACILITY_RPC				1
#define FACILITY_SYSTEM				7
#define FACILITY_CONTROL			10
#define FACILITY_NULL				0
#define FACILITY_METADIRECTORY		35
#define FACILITY_INTERNET			12
#define FACILITY_IOBJECT			2
#define FACILITY_CONFIGURATION		33
#define FACILITY_BACKGROUNDCOPY		32

//
// Macros for error handling
//

#define MAKE_RESULT(sev,fac,code)												\
	( (Result) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16)			\
		| ((unsigned long)(code))) )

#define RESULT_CODE(r)				((r) & 0xFFFF)

#define RESULT_FACILITY(r)			(((r) >> 16) & 0xff)

#ifndef HRESULT_SEVERITY
#define HRESULT_SEVERITY(r)			(((r) >> 31) & 0x1)
#endif // !HRESULT_SEVERITY

#define IS_ERROR(Status)			((unsigned long)(Status) >> 31 == SEVERITY_ERROR)

#ifndef SUCCEEDED

#define SUCCEEDED(Status)			((long)(Status) >= 0)

#define FAILED(Status)				((long)(Status) < 0)

#endif // !SUCCEEDED

/************************************************************************

	Standart error codes description:
		E_ABORT			The operation was aborted because of an unspecified error. 
		E_ACCESSDENIED	A general access-denied error. 
		E_FAIL			An unspecified failure has occurred. 
		E_HANDLE		An invalid handle was used. 
		E_INVALIDARG	One or more arguments are invalid. 
		E_NOINTERFACE	The QueryInterface method did not recognize the requested 
						interface. The interface is not supported. 
		E_NOTIMPL		The method is not implemented. 
		E_OUTOFMEMORY	The method failed to allocate necessary memory. 
		E_PENDING		The data necessary to complete the operation is not yet 
						available. 
		E_POINTER		An invalid pointer was used. 
		E_UNEXPECTED	A catastrophic failure has occurred. 
		S_FALSE			The method succeeded and returned the boolean value FALSE. 
		S_OK			The method succeeded. If a boolean return value is expected, 
						the returned value is TRUE. 		

************************************************************************/

//
// Define standart error codes
// 

#ifndef E_ABORT

#define E_ABORT						((result)0x80004004L)
#define E_ACCESSDENIED				((result)0x80070005L) 
#define E_FAIL						((result)0x80004005L)
#define E_HANDLE					((result)0x80070006L) 
#define E_INVALIDARG				((result)0x80070057L) 
#define E_NOINTERFACE				((result)0x80004002L)
#define E_NOTIMPL					((result)0x80004001L) 
#define E_OUTOFMEMORY				((result)0x8007000EL)
#define E_PENDING					((result)0x8000000AL) 
#define E_POINTER					((result)0x80004003L) 
#define E_UNEXPECTED				((result)0x8000FFFFL) 
#define S_FALSE						((result)0x00000001L) 
#define S_OK						((result)0x00000000L) 

#endif // !E_ABORT

//
// Advanced error codes. File system
//

#ifndef STG_E_FILENOTFOUND

// Standsrt error codes
#define STG_E_FILENOTFOUND			((result)0x80030002L)
#define STG_E_INVALIDHEADER			((result)0x800300FBL)

#define CLASS_E_CLASSNOTAVAILABLE	((result)0x80040111L)
#define CLASS_E_NOAGGREGATION		((result)0x80040110L)

#define REGDB_E_CLASSNOTREG         ((result)0x80040154L)

#endif // !STG_E_FILENOTFOUND

// Custom Data Processing SDK error codes
#define STG_E_INVALIDFORMAT			((result)0x80030106L)

// Custom Components SDK error codes
#define COMP_E_INVALIDCOMPONENT			((result)0x80030201L)
#define COMP_E_NOTLOADED				((result)0x80030202L)
#define COMP_E_ALREADYINITIALIZED		((result)0x80030203L)
#define COMP_E_ERRORDLOADING			((result)0x80030204L)
#define COMP_E_INTERFACENOTSUPPORTED	((result)0x80030205L)

#endif // !ERRORCODES_H__COMMON__INCLUDED_
