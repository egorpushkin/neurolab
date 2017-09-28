#ifndef ERRORCODES_H__TRAINERSMANAGER__INCLUDED_
#define ERRORCODES_H__TRAINERSMANAGER__INCLUDED_

/************************************************************************

	RESULT bit structure:
		
		|31         24|23           16|15            8|7             0|
		| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 
		|s| Reserved  |   Facility    |           Error code          |

	RESULT fields description:
		The facility field indicates the system service responsible 
		for the error.	

************************************************************************/

//
// Define the facility codes
// 

#define FACILITY_TRAINERS			0x80

#define TR_E_LOADERNOTSPECIFIED		((result)0x80800001L)
#define TR_E_WRONGTRAINERLIB		((result)0x80800002L)
#define TR_E_INFOVERNOTSUPPORTED	((result)0x80800003L)

#endif // !ERRORCODES_H__TRAINERSMANAGER__INCLUDED_
