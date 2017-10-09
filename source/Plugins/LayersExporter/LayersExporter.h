// LayersExporter.h : main header file for the LayersExporter DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CLayersExporterApp
// See LayersExporter.cpp for the implementation of this class
//

class CLayersExporterApp : public CWinApp
{
public:
	CLayersExporterApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
