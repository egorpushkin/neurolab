// HopfieldLearning.h : main header file for the HopfieldLearning DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CHopfieldLearningApp
// See HopfieldLearning.cpp for the implementation of this class
//

class CHopfieldLearningApp : public CWinApp
{
public:
	CHopfieldLearningApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
