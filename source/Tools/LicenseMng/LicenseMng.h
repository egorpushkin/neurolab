// LicenseMng.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CLicenseMngApp:
// See LicenseMng.cpp for the implementation of this class
//

class CLicenseMngApp : public CWinApp
{
public:
	CLicenseMngApp();

	CString GetAppFolder()
	{
		return csAppFolder;
	}

// Overrides
	public:
	virtual BOOL InitInstance();
  
// Implementation

	DECLARE_MESSAGE_MAP()

private:
	CString						csAppFolder;
};

extern CLicenseMngApp theApp;