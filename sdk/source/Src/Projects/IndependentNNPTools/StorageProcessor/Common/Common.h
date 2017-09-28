//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: Common.h
//	Description: Common shared structures declaration.  

#ifndef COMMON_H__STORAGEPROCESSOR__INCLUDED_
#define COMMON_H__STORAGEPROCESSOR__INCLUDED_

namespace StorageProcessorCommonKit
{

	#include "ExternalStorage.h"
	#include "ErrorCodes.h"

	#include "StorageFlags.h"

	#include "Interfaces/IConfig.h"
	#include "Interfaces/IExternalSerializer.h"
	#include "Interfaces/IStorageProcessor.h"

	#include "IID.h"	
	#include "CLSID.h"	

}

namespace StorageProcessorKit = StorageProcessorCommonKit;
namespace SpKit = StorageProcessorCommonKit;

#endif // !COMMON_H__STORAGEPROCESSOR__INCLUDED_
