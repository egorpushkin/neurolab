#include "StdAfx.h"
#include "MLotTransform.h"

#include "Math.h"

#include "..\..\LuaEngine\LuaApiMacro.h"

#include "CmnDataFactory.h"

#include "..\..\..\..\TransformationEngines\EnginesInclude.h"

// Fast Discrete Cosine Transform, type IV
int LuaMLotTransform_FDCS4(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)

    int tmDataLength = log10((float)pDataFactory->GetDataLength()) / 
		log10(2.0f);
	fdctiv(pDataFactory->GetData(), tmDataLength);

	return true;
}
