//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StorageProcesssor.h
//	Description: Component includes and intial declarations.  

#ifndef STORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_
#define STORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_

#define STORAGEPROCESSOR_FUNC_DECLARE EXPORT_SYMBOL_SIGNATURE

// Including Network Importing SDK headers
#define _GUIDS_	NetworkImportingDllGuidsDef
#include "NetworkImporting/NetworkImportingKit.h"

// Old versions compatibility trick
namespace MinCOM
{	
	using namespace CommonKit;
}

// Smart objects containing and enumeration
#include "Common/ContainerNew/Container.h"

// Including Storage Processor Common headers
#include "Common/Common.h"

// Including external components
#include "ExternalComponents.h"

#endif // !STORAGEPROCESSOR_H__STORAGEPROCESSOR__INCLUDED_
