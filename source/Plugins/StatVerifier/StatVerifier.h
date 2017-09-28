// StatVerifier.h : main header file for the StatVerifier DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CStatVerifierApp
// See StatVerifier.cpp for the implementation of this class
//

class CStatVerifierApp : public CWinApp
{
public:
	CStatVerifierApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
