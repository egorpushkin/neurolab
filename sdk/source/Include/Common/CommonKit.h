//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CommonKit.h
//	Description: Common SDK main include file.   

//	Include this file in your solution to add functionality of this SDK.

#ifndef COMMONKIT_H__COMMON__INCLUDED_
#define COMMONKIT_H__COMMON__INCLUDED_

/*!	\brief			Component model core interface.
*	\author			Egor Pushkin
*	\version		1.0.0.1
*	\date			07.06.2006
*	\par			License:
*		This code is a part of 'Common SDK' product.
*		Copyright (C) Scientific Software 2006
*/

#include "Common/STL.h"
#include "Common/Common.h"
#include "Common/GUID.h"

#include "Loki/SmartPtr.h"

namespace CommonKit
{
		
	#include "Common/String.h"
	#include "Common/ErrorCodes.h"

	#include "Common/SmartPointers.h"

	#include "Common/ICommon.h"
	#include "Common/ICommonFactory.h"
	#include "Common/Macros.h"

	#include "Common/Tools/QueryTool.h"
	#include "Common/Tools/ConstructTool.h"
	#include "Common/Tools/Guid.h"

	#include "IID.h"

	#include "Common/Factory.h"

	#include "Model/CommonImplOld.h"
	#include "Model/CommonImpl.h"

	#include "Variant/CommonVariant.h"
	#include "Variant/CommonEnum.h"

	#include "Container/IEnumerator.h"
	#include "Container/IContainer.h"
	#include "Container/Policy/StoragePolicy.h"
	#include "Container/Policy/CopyPolicy.h"
	#include "Container/Policy/ReferencesPolicy.h"
	#include "Container/Enumerator.h"
	#include "Container/Container.h"

}

#include "Std/Guid.h"

#endif // !COMMONKIT_H__COMMON__INCLUDED_
