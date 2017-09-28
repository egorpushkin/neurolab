// PCABlockset.h : main header file for the PCABlockset DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CPCABlocksetApp
// See PCABlockset.cpp for the implementation of this class
//

class CPCABlocksetApp : public CWinApp
{
public:
	CPCABlocksetApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
