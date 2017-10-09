// RBFTraining.h : main header file for the RBFTraining DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CRBFTrainingApp
// See RBFTraining.cpp for the implementation of this class
//

class CRBFTrainingApp : public CWinApp
{
public:
	CRBFTrainingApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
