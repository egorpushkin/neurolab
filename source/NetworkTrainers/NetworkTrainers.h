// NetworkTrainers.h : main header file for the NetworkTrainers DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CNetworkTrainersApp
// See NetworkTrainers.cpp for the implementation of this class
//

class CNetworkTrainersApp : public CWinApp
{
public:
	CNetworkTrainersApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
