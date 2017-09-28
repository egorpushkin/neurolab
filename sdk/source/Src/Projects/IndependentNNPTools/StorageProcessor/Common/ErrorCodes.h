//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: ErrorCodes.h
//	Description: Error codes mechanizm implementation.  

#ifndef ERRORCODES_H__STORAGEPROCESSOR__INCLUDED_
#define ERRORCODES_H__STORAGEPROCESSOR__INCLUDED_

//
// Define the facility code for Network Importing SDK errors
// 

#define FACILITY_STORAGE_PROC_SDK	0x60

//
// Define network importing and processing error codes
//

// XML document writing errors
#define SP_XML_E_STARTDOC			((result)0x80600201L)
#define SP_XML_E_ADDELEMENT			((result)0x80600202L)
#define SP_XML_E_ENDDOC				((result)0x80600203L)
#define SP_XML_E_ADDATTRIBUTE		((result)0x80600204L)
#define SP_XML_E_ENDELEMENT			((result)0x80600205L)

// XML document parsing errors
#define SP_XML_E_NOROOT				((result)0x80600301L)
#define SP_XML_E_WRONGFORMAT		((result)0x80600302L)
#define SP_XML_E_WRONGELEMENTNAME	((result)0x80600303L)
#define SP_XML_E_WRONGEXTERNALDATA	((result)0x80600304L)
#define SP_XML_E_WRONGARGUMENTTYPE	((result)0x80600305L)

// Building network errors (IStructureBuilder API)
#define SP_E_QUERYBUILDER			((result)0x80600401L)
#define SP_E_WRONGELEMENTOBJECT		((result)0x80600402L)
#define SP_E_BUILDERALLOCATEERROR	((result)0x80600403L)



#endif // !ERRORCODES_H__STORAGEPROCESSOR__INCLUDED_
