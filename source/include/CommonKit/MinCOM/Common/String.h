#ifndef STRING_H__MINCOM__COMMONKIT__INCLUDED_
#define STRING_H__MINCOM__COMMONKIT__INCLUDED_

#ifdef _UNICODE

#ifndef _T
#define _T(x)                        L ## x
#endif

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED

typedef wchar_t                      TCHAR;

#endif // !__TCHAR_DEFINED

#else // _UNICODE

#ifndef _T
#define _T(x)                        x
#endif

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED

typedef char                         TCHAR;

#endif // !__TCHAR_DEFINED

#endif // _UNICODE

#ifndef _WINNT_

typedef TCHAR*                       LPTSTR;
typedef const TCHAR*                 LPCTSTR;

// Multi-byte string macros
typedef char*                        LPSTR;
typedef const char*                  LPCSTR;

// Unicode string macros
typedef wchar_t*                     LPUSTR;
typedef const wchar_t*               LPCUSTR;

#endif // !_WINNT_

// Declaring object model main string container
typedef std::basic_string< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >			String;
typedef std::basic_string< char, std::char_traits<char>, std::allocator<char> >				StringA;
typedef std::basic_string< wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >	StringU;


#endif // !STRING_H__COMMON__INCLUDED_
