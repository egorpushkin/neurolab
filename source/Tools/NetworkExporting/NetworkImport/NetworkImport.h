// NetworkImport.h : main header file for the NetworkImport DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CNetworkImportApp
// See NetworkImport.cpp for the implementation of this class
//

class CNetworkImportApp : public CWinApp
{
public:
	CNetworkImportApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
