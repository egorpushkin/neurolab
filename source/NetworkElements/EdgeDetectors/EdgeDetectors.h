// EdgeDetectors.h : main header file for the EdgeDetectors DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CEdgeDetectorsApp
// See EdgeDetectors.cpp for the implementation of this class
//

class CEdgeDetectorsApp : public CWinApp
{
public:
	CEdgeDetectorsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
