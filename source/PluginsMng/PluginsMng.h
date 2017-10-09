// PluginsMng.h : main header file for the PluginsMng DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CPluginsMngApp
// See PluginsMng.cpp for the implementation of this class
//

class CPluginsMngApp : public CWinApp
{
public:
	CPluginsMngApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
