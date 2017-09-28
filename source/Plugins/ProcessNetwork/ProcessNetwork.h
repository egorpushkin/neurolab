// ProcessNetwork.h : main header file for the ProcessNetwork DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CProcessNetworkApp
// See ProcessNetwork.cpp for the implementation of this class
//

class CProcessNetworkApp : public CWinApp
{
public:
	CProcessNetworkApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
