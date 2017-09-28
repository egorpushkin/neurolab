#include "stdafx.h"

#include "../Common/Includes.h"

namespace LTILib
{

	LTILibPackage::LTILibPackage()
		: LuaKit::PackageImpl()
	{
		LuaKit::PackageImpl::SetInfo(
			"lti", 
			"LTI-Lib 1.9.15", 
			"LTI-Lib Bindings 1.0.0.1", 
			"lti{any}");
	}

}
