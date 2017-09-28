#ifndef TYPES_H__MINCOM__COMMONKIT__INCLUDED_
#define TYPES_H__MINCOM__COMMONKIT__INCLUDED_

namespace Types
{

	#ifndef __USE_MISC
		#define __mc__UTYPES_DEFINED
		typedef unsigned int            uint;	
		typedef unsigned short int      ushort;
		typedef unsigned long int       ulong;
	#endif // !__USE_MISC

	//typedef unsigned char               byte;
	typedef unsigned short              word;	
	typedef unsigned int				uint_ptr;
	typedef long                        long_ptr;
	typedef unsigned long               dword;
	typedef unsigned long               dword_ptr;
	typedef unsigned long               ulong_ptr;

	typedef void*                       pvoid;
	typedef void*                       handle;
	typedef void*                       hwnd;

	typedef long_ptr                    wparam;
	typedef long_ptr                    lparam;

	#ifndef _TYPE_RESULT_DEFINED
	#define _TYPE_RESULT_DEFINED
		typedef long result;
	#endif // !_TYPE_RESULT_DEFINED

}

using namespace Types;

#endif // !TYPES_H__MINCOM__COMMONKIT__INCLUDED_
