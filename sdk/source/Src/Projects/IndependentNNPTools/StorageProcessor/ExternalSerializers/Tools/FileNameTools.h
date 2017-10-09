//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: FileNameTools.h
//	Description: File name operations declaration.  

#ifndef FILENAMETOOLS_H__STORAGEPROCESSOR__INCLUDED_
#define FILENAMETOOLS_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

StringA GetProjectName(
	const StringA& fileName
);

StringA GetProjectFilePath(
	const StringA& fileName
);

#endif // !FILENAMETOOLS_H__STORAGEPROCESSOR__INCLUDED_
