//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DataProcessing.h
//	Description: Data Processing SDK main include file.   

//	Include this file in your solution to add functionality of this SDK.

#ifndef DATAPROCESSINGKIT_H__DATAPROCESSING__INCLUDED_
#define DATAPROCESSINGKIT_H__DATAPROCESSING__INCLUDED_

// Including functionality of Common SDK
#include "../Common/CommonKit.h"

using namespace CommonKit;

namespace DataProcessingKit
{
	
	#include "Common/FileIO.h"
	#include "Common/XML.h"
	#include "Common/BMPFormat.h"
	#include "Common/IStorageController.h"

	#include "Interfaces/IDataFactory.h"
	#include "Interfaces/IPGMFactory.h"
	#include "Interfaces/IBMPFactory.h"
	#include "Interfaces/IDataFile.h"
	#include "Interfaces/IDataBitmap.h"
	#include "Interfaces/IPGMBitmap.h"

	#include "Implementations/DataFactory.h"
	#include "Implementations/PGMFactory.h"
	#include "Implementations/BMPFactory.h"
	#include "Implementations/DataFile.h"
	#include "Implementations/DataBitmap.h"
	#include "Implementations/PGMBitmap.h"

	#include "IID.h"
}

#endif // !DATAPROCESSINGKIT_H__DATAPROCESSING__INCLUDED_
