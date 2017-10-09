//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Common.h
//	Description: Common shared structures declaration.  

//	Include this file in your solution to use functionality of this component.
//	Be sure that you've already included NetworkImportingKit.h.

//	Compile this code with WIN32_EXTERNAL_OUTPUT_ENGINE macro declared to add
//		support of visual editor environment functionality to all network comonents. 
//		Note that you have to include required system dependent headers and 
//		libraries supported by visual editor control. Otherwise library use custom 
//		output engine stub. See 'OutputEngine.h' for details.

#ifndef COMMON_H__BUILDERELEMENTS__INCLUDED_
#define COMMON_H__BUILDERELEMENTS__INCLUDED_

// Vwerify whether external network output device presents
#ifndef WIN32_EXTERNAL_OUTPUT_ENGINE

// Notify library code 
#define USING_INTERNAL_OUTPUT_ENGINE_STUB

namespace ExternalOutputEngine
{
	#include "OutputEngine.h"
}

#endif // !WIN32_EXTERNAL_OUTPUT_ENGINE

namespace BuilderElementsCommonKit
{

	#include "Element.h"
	
	#include "Interfaces/IFunctionsFactory.h"
	#include "Interfaces/IElementsContainer.h"
	#include "Interfaces/IGroupsContainer.h"
	#include "Interfaces/IFactoryControl.h"
	#include "Interfaces/IBuilderElement.h"

	#include "IID.h"	
	#include "CLSID.h"	

	#include "Elements/CmnElement.h"
	#include "Elements/CmnDataFlow.h"
	#include "Elements/CmnDataConnector.h"
	#include "Elements/CmnBuilderElement.h"
	#include "Elements/CmnLayer.h"

}

#endif // !COMMON_H__BUILDERELEMENTS__INCLUDED_
