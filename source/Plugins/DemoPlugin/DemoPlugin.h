// DemoPlugin.h : main header file for the DemoPlugin DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CDemoPluginApp
// See DemoPlugin.cpp for the implementation of this class
//

class CDemoPluginApp : public CWinApp
{
public:
	CDemoPluginApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
