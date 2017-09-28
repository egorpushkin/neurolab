#ifndef INCLUDES_H__S2DCHARTING__INCLUDED_
#define INCLUDES_H__S2DCHARTING__INCLUDED_

#include "loki/StrongPtr.h"

#include <string>
#include <vector>
#include <exception>
#include <limits>

#ifndef _TYPE_RESULT_DEFINED
#define _TYPE_RESULT_DEFINED
typedef long result;
#endif // !_TYPE_RESULT_DEFINED

namespace Simple2dCharting
{

	static const result OK = ((result)0x00000000L);
	static const result FAIL	= ((result)0x80004005L);

}

#endif // !INCLUDES_H__S2DCHARTING__INCLUDED_
