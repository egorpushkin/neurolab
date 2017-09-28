// BackPropagationFann.h : main header file for the BackPropagationFann DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CBackPropagationFannApp
// See BackPropagationFann.cpp for the implementation of this class
//

class CBackPropagationFannApp : public CWinApp
{
public:
	CBackPropagationFannApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
