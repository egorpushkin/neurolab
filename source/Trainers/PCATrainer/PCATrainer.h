// PCATrainer.h : main header file for the PCATrainer DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CPCATrainerApp
// See PCATrainer.cpp for the implementation of this class
//

class CPCATrainerApp : public CWinApp
{
public:
	CPCATrainerApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
