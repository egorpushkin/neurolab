#ifndef GETOPTINCLUDE_H__GNUC_CORE__INCLUDED_
#define GETOPTINCLUDE_H__GNUC_CORE__INCLUDED_

// Include platform support for console applications developemnt
#ifdef _MSC_VER 

#include "getopt/getopt.h"

#define DECLARE_GETOTP_TOOL			getopt_tool gt;
#define GETOPT_CALL					gt.getopt_long
#define GETOPT_ARG					gt.optarg

#else 

#include <getopt.h>

#define DECLARE_GETOTP_TOOL			
#define GETOPT_CALL					getopt_long
#define GETOPT_ARG					optarg

#endif // _MSC_VER 

#endif // !GETOPTINCLUDE_H__GNUC_CORE__INCLUDED_




