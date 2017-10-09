// ScriptEnv.h : main header file for the ScriptEnv DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CScriptEnvApp
// See ScriptEnv.cpp for the implementation of this class
//

class CScriptEnvApp : public CWinApp
{
public:
	CScriptEnvApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
