// OutputLib.h : main header file for the OutputLib DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// COutputLibApp
// See OutputLib.cpp for the implementation of this class
//

class COutputLibApp : public CWinApp
{
public:
	COutputLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
