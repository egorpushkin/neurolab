//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: PrepareDataFileName.h
//	Description: The PrepareDataFileName routine declaration.  

#ifndef PREPAREDATAFILENAME_H__STORAGEPROCESSOR__INCLUDED_
#define PREPAREDATAFILENAME_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

StringA PrepareDataFileName(
	const StringA& projectName, 
	const StringA& elementSysName, 
	uint elementID,
	const StringA& fileSuffix
);

#endif // !PREPAREDATAFILENAME_H__STORAGEPROCESSOR__INCLUDED_
