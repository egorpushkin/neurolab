//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: NetworkImportingKit.h
//	Description: Network Importing SDK main include file.   

//	Include this file in your solution to add functionality of this SDK.

#ifndef NETWORKIMPORTING_H__NETWORKIMPORTING__INCLUDED_
#define NETWORKIMPORTING_H__NETWORKIMPORTING__INCLUDED_

// Including functionality of Common SDK
#include "../DataProcessing/DataProcessingKit.h"
#include "../Components/ComponentsKit.h"

using namespace DataProcessingKit;
using namespace ComponentsKit;

namespace NetworkImportingKit
{

	#include "Common/DefElement.h"
	#include "Common/ErrorCodes.h"

	#include "Implementations/Function.h"
	#include "Implementations/Connection.h"

	#include "Interfaces/IElement.h"
	#include "Interfaces/IDataFlow.h"
	#include "Interfaces/IConnectionsFactory.h"
	#include "Interfaces/IDataConnector.h"
	#include "Interfaces/ILayerControl.h"

	#include "Implementations/ConnectionsFactory.h"

	#include "Interfaces/IElementsCollection.h"
	#include "Interfaces/INetworkProcessor.h"
	#include "Interfaces/IStructureBuilder.h"

	#include "Interfaces/IImportManager.h"
	
	#include "IID.h"
	#include "CLSID.h"

}

#endif // !NETWORKIMPORTING_H__NETWORKIMPORTING__INCLUDED_
