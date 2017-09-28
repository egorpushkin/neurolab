// BuilderElements.h : main header file for the BuilderElements DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CBuilderElementsApp
// See BuilderElements.cpp for the implementation of this class
//

class CBuilderElementsApp : public CWinApp
{
public:
	CBuilderElementsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
