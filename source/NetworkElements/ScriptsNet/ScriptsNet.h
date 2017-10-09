// ScriptsNet.h : main header file for the ScriptsNet DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CScriptsNetApp
// See ScriptsNet.cpp for the implementation of this class
//

class CScriptsNetApp : public CWinApp
{
public:
	CScriptsNetApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
