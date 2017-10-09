#ifndef __BCGCBPROINC_H
#define __BCGCBPROINC_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include <afxpriv.h>

#if _MSC_VER >= 1300
	#include <..\atlmfc\src\mfc\afximpl.h>
#else
	#include <..\src\afximpl.h>
#endif

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#endif // _AFX_NO_OLE_SUPPORT

#define _BCGPEDIT_STANDALONE	// Use BCG Edit Control
/*#ifdef _BCGCBPRO_IN_OTHER_DLL
BCGCBPRODLLEXPORT void BCGCBPRODllInitialize ();
#endif // _BCGCBPRO_IN_OTHER_DLL*/

/*#if defined _AFXDLL && !defined _BCGPEDIT_STATIC_
	//------------------------------------
	// MFC shared DLL, BCGPEdit shared DLL
	//------------------------------------
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGPEdit730UD.lib") 
			#pragma message("Automatically linking with BCGPEdit730UD.dll")
		#else
			#pragma comment(lib,"BCGPEdit730D.lib") 
			#pragma message("Automatically linking with BCGPEdit730D.dll")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGPEdit730U.lib") 
			#pragma message("Automatically linking with BCGPEdit730U.dll") 
		#else
			#pragma comment(lib,"BCGPEdit730.lib") 
			#pragma message("Automatically linking with BCGPEdit730.dll") 
		#endif
	#endif
#elif defined _BCGPEDIT_STATIC_
	//----------------------------------------
	// MFC shared DLL, BCGPEdit static library
	//----------------------------------------
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGPEditStatic730UDS.lib") 
			#pragma message("Automatically linking with BCGPEditStatic730UDS.lib") 
		#else
			#pragma comment(lib,"BCGPEditStatic730DS.lib") 
			#pragma message("Automatically linking with BCGPEditStatic730DS.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGPEditStatic730US.lib") 
			#pragma message("Automatically linking with BCGPEditStatic675US.lib") 
		#else
			#pragma comment(lib,"BCGPEditStatic730S.lib") 
			#pragma message("Automatically linking with BCGPEditStatic730S.lib") 
		#endif
	#endif
#else
	//--------------------------------------------
	// MFC static library, BCGPEdit static library
	//--------------------------------------------
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGPEditStatic730UD.lib") 
			#pragma message("Automatically linking with BCGPEditStatic730UD.lib") 
		#else
			#pragma comment(lib,"BCGPEditStatic730D.lib") 
			#pragma message("Automatically linking with BCGPEditStatic730D.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGPEditStatic730U.lib") 
			#pragma message("Automatically linking with BCGPEditStatic730U.lib") 
		#else
			#pragma comment(lib,"BCGPEditStatic730.lib") 
			#pragma message("Automatically linking with BCGPEditStatics730.lib") 
		#endif
	#endif
#endif*/

//-------------
// BCG helpers:
//-------------
#include "BCGPDrawManager.h"

//--------------
// BCG controls:
//--------------
#include "BCGPEditCtrl.h"
#include "BCGPIntelliSenseWnd.h"
#include "BCGPIntelliSenseLB.h"
#include "BCGPOutlineParser.h"

//-----------
// BCG views:
//-----------
#include "BCGPEditView.h"

#endif // __BCGCBPROINC_H
