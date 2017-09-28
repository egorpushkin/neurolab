//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ComponentsKit.h
//	Description: Components SDK main include file.   

//	Include this file in your solution to add functionality of this SDK.

#ifndef COMPONENTSKIT_H__COMPONENTS__INCLUDED_
#define COMPONENTSKIT_H__COMPONENTS__INCLUDED_

// Including functionality of Common SDK
#include "../Common/CommonKit.h"

using namespace CommonKit;

namespace ComponentsKit
{

	#include "Common/SharedObjects.h"	
	#include "Common/IComponentLoader.h"

	#include "Implementations/ComponentLoader.h"
	#include "Implementations/CommonFactoryImpl.h"

	#include "Externals/ICHF.h"

	#include "IID.h"
	#include "CLSID.h"

}

#endif // !COMPONENTSKIT_H__COMPONENTS__INCLUDED_
