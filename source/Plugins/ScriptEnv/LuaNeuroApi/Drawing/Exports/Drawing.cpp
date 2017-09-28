#include "stdafx.h"

#include "../Common/Includes.h"

namespace Drawing
{

	DrawingPackage::DrawingPackage()
		: LuaKit::PackageImpl()
	{
		LuaKit::PackageImpl::SetInfo(
			"drawing", 
			"Drawing Control 1.0.0.1", 
			"Drawing Control 1.0.0.1", 
			"drawing{any}");
	}

}
