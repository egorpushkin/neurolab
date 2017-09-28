#ifndef USINGS_H__MINCOM__COMMONKIT__INCLUDED_
#define USINGS_H__MINCOM__COMMONKIT__INCLUDED_

#ifndef __DONT_USE_COMMON_TYPES

	using namespace MinCOM::Types;

	#ifndef _WINNT_

		using MinCOM::LPTSTR;
		using MinCOM::LPCTSTR;
		using MinCOM::LPSTR;
		using MinCOM::LPCSTR;
		using MinCOM::LPUSTR;
		using MinCOM::LPCUSTR;

	#endif // !_WINNT_

	using MinCOM::String;
	using MinCOM::StringA;
	using MinCOM::StringU;

#endif // !_DONT_USE_COMMON_TYPES

#ifdef __mc__GUID_DEFINED

/*	using MinCOM::GUID;
	using MinCOM::IID;
	using MinCOM::CLSID;*/

/*	using MinCOM::REFGUID;
	using MinCOM::REFIID;
	using MinCOM::REFCLSID;*/

#endif // __mci__GUID_DEFINED

#endif // !USINGS_H__MINCOM__COMMONKIT__INCLUDED_
