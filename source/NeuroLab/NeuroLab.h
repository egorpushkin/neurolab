// NeuroLab.h : main header file for the NeuroLab application
//
#pragma once

#ifndef SOURCE_NEUROLAB_EXTERNAL
#define SOURCE_NEUROLAB_INTERNAL
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CNeuroLabApp:
// See NeuroLab.cpp for the implementation of this class
//

#include "Loader\ComponentsLoader.h"
#include "Components\ComponentsContainer.h"

class CNeuroLabApp : public CWinApp
{
public:
	CNeuroLabApp();

	CComponentsContainer		mComponents;
	CComponentsLoader			mAppLoader;

#ifdef SOURCE_NEUROLAB_INTERNAL
	GdiplusStartupInput			gdiplusStartupInput;
	ULONG_PTR					gdiplusToken;
#endif

	CString						GetAppFolder();

private:
	CString						csAppFolder;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual void OnFinalRelease();
};

extern CNeuroLabApp theApp;