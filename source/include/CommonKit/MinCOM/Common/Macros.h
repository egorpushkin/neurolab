#ifndef MACROS_H__MINCOM__COMMONKIT__INCLUDED_
#define MACROS_H__MINCOM__COMMONKIT__INCLUDED_

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)      { if(p) { delete (p);     (p)=NULL; } }
#endif // SAFE_DELETE
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)     { if(p) { (p)->Release(); (p)=NULL; } }
#endif // SAFE_RELEASE

#define MAX(a, b)           ( (a) > (b) ? (a) : (b) )

#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((word)(((byte)((dword_ptr)(a) & 0xff)) | ((word)((byte)((dword_ptr)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((long)(((word)((dword_ptr)(a) & 0xffff)) | ((dword)((word)((dword_ptr)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((word)((dword_ptr)(l) & 0xffff))
#define HIWORD(l)           ((word)((dword_ptr)(l) >> 16))
#define LOBYTE(w)           ((byte)((dword_ptr)(w) & 0xff))
#define HIBYTE(w)           ((byte)((dword_ptr)(w) >> 8))
#endif // !MAKEWORD

#endif // !MACROS_H__MINCOM__COMMONKIT__INCLUDED_
