// KohonenTraining.h : main header file for the KohonenTraining DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CKohonenTrainingApp
// See KohonenTraining.cpp for the implementation of this class
//

class CKohonenTrainingApp : public CWinApp
{
public:
	CKohonenTrainingApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
