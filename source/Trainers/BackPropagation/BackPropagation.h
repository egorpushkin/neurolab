// BackPropagation.h : main header file for the BackPropagation DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CBackPropagationApp
// See BackPropagation.cpp for the implementation of this class
//

class CBackPropagationApp : public CWinApp
{
public:
	CBackPropagationApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
