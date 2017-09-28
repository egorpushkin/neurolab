//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: STL.h
//	Description: STL include file.  

#ifndef STL_H__COMMON__INCLUDED_
#define STL_H__COMMON__INCLUDED_

//////////////////////////////////////////////////////////////////////////
// This header file requires native compiler STL support /////////////////
//////////////////////////////////////////////////////////////////////////

//
// Including required containers
//

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4702 )
#endif // _MSC_VER

#include <iterator>
#include <vector>
#include <list>
#include <map>
#include <string>

#ifdef _MSC_VER
#pragma warning( pop )
#endif // _MSC_VER

//
// Including required STL tools
//

#include <cassert>
#include <memory>
#include <algorithm>

//
// Including standart exception mechanism
//

#include <stdexcept>

//
// Using standart namespace
//

using namespace std;

#endif // !STL_H__COMMON__INCLUDED_
