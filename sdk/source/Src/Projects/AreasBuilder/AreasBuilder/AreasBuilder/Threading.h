#ifndef THREADING_H__AREASBUILDER__INCLUDED_
#define THREADING_H__AREASBUILDER__INCLUDED_

namespace AreasBuilder
{

#include <process.h>

typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define	__beginthreadex(psa, cbStack, pfnStartAddr,		\
	pvParam, fdwCreate, pdwThreadId)					\
		((handle)_beginthreadex(						\
			(void *)        (psa),						\
			(unsigned)      (cbStack),					\
			(PTHREAD_START) (pfnStartAddr),				\
			(void *)        (pvParam),					\
			(unsigned)      (fdwCreate),				\
			(unsigned *)    (pdwThreadId)))

}

#endif // !THREADING_H__AREASBUILDER__INCLUDED_
