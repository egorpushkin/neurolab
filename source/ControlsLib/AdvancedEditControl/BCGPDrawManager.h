// BCGDrawManager.h: interface for the CBCGPDrawManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__BCGPDRAWMANAGER_H)
#define __BCGPDRAWMANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGCBPro.h"

class BCGCBPRODLLEXPORT CBCGPDrawManager : public CObject
{
public:
	CBCGPDrawManager(CDC&);
	virtual ~CBCGPDrawManager();

// Operatioins:
	void FillGradient (	CRect rect, 
						COLORREF colorStart, COLORREF colorFinish,
						BOOL bHorz = TRUE,
						int nStartFlatPercentage = 0,
						int nEndFlatPercentage = 0);

	void FillGradient2 (CRect rect, COLORREF colorStart, COLORREF colorFinish, 
						int nAngle = 0 /* 0 - 360 */);
// Helpers:
	static COLORREF PixelAlpha (COLORREF srcPixel, int percent);

// Conversion between the HSL (Hue, Saturation, and Luminosity) 
	static double HuetoRGB (double m1, double m2, double h);
	static COLORREF HLStoRGB_ONE (double H, double L, double S);
	static void RGBtoHSL (COLORREF rgb, double *H, double *S, double *L);

// Attributes:
protected:
	CDC&	m_dc;
};

#endif // !defined(__BCGPDRAWMANAGER_H)
