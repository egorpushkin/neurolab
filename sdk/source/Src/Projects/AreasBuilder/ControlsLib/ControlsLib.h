// ControlsLib.h : main header file for the ControlsLib DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CControlsLibApp
// See ControlsLib.cpp for the implementation of this class
//

class CControlsLibApp : public CWinApp
{
public:
	CControlsLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
