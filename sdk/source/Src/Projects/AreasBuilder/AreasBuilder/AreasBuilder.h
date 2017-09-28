// AreasBuilder.h : main header file for the AreasBuilder application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CAreasBuilderApp:
// See AreasBuilder.cpp for the implementation of this class
//

class CAreasBuilderApp : public CWinApp
{
public:
	CAreasBuilderApp();

	// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual void OnFinalRelease();
};

extern CAreasBuilderApp theApp;