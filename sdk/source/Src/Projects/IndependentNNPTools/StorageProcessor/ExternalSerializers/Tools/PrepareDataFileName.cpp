//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: PrepareDataFileName.cpp
//	Description: The PrepareDataFileNmae routine implementation.  

#include "PrepareDataFileName.h"

StringA PrepareDataFileName(
	const StringA& projectName, 
	const StringA& elementSysName, 
	uint elementID,
	const StringA& fileSuffix)
{
	char tmElementId[10];
	sprintf(tmElementId, "%d", elementID);

    StringA result = 
		projectName + StringA("_") + 
		elementSysName + StringA("_") + 
		StringA(tmElementId) + StringA("_") + 
		fileSuffix + 
		StringA(".") + 
		StringA(DATA_FILE_EXTENSION);

	return result;
}
