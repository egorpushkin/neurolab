#ifndef MINCOM_H__MINCOM__COMMONKIT__INCLUDED_
#define MINCOM_H__MINCOM__COMMONKIT__INCLUDED_

#include "ExternalIncludes.h"

#include "Loki/SmartPtr.h"

#define INITGUID
#include "Common/Guiddef.h"

namespace MinCOM
{

	#include "Common/Common.h"
	#include "Common/Types.h"
	#include "Common/String.h"
	#include "Common/ErrorCodes.h"
	#include "Common/Macros.h"
	#include "Common/SmartPointers.h"

	#include "Interfaces/ICommon.h"
	#include "Interfaces/ICommonFactory.h"
	#include "Interfaces/IID.h"

	#include "Model/CommonImpl.h"

	#include "Common/Factory.h"

}

#include "Common/Usings.h"

#include "Std/Guid.h"
#include "Loki/Factory.h"

#endif // !MINCOM_H__MINCOM__COMMONKIT__INCLUDED_
