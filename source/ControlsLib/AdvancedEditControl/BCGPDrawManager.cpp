// BCGDrawManager.cpp: implementation of the CBCGPDrawManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "BCGCBPro.h"
#include "BCGPDrawManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const double PI = 3.1415926;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGPDrawManager::CBCGPDrawManager(CDC& dc) : m_dc (dc)
{
}
//*************************************************************************************
CBCGPDrawManager::~CBCGPDrawManager()
{
}

// ==================================================================
// 
// FUNCTION :  PixelAlpha ()
// 
// * Description : Shades a color value with a specified percentage
// 
// * Author : [Timo Hummel], Created : [8/11/99 2:37:04 PM]
// 
// * Returns : [COLORREF] - The result pixel
// 
// * Function parameters : 
// [srcPixel] - The source pixel
// [percent] -  Percentage (amount of shadow)
//
// Example: percent = 10    makes the pixel around 10 times darker
//          percent = 50    makes the pixel around 2 times darker
// 
// ==================================================================
COLORREF CBCGPDrawManager::PixelAlpha (COLORREF srcPixel, int percent)
{
	// My formula for calculating the transpareny is as
	// follows (for each single color):
	//
	//							   percent
	// destPixel = sourcePixel * ( ------- )
	//                               100
	//
	// This is not real alpha blending, as it only modifies the brightness,
	// but not the color (a real alpha blending had to mix the source and
	// destination pixels, e.g. mixing green and red makes yellow).
	// For our nice "menu" shadows its good enough.

	COLORREF clrFinal = RGB ( min (255, (GetRValue (srcPixel) * percent) / 100), 
							  min (255, (GetGValue (srcPixel) * percent) / 100), 
							  min (255, (GetBValue (srcPixel) * percent) / 100));

	return (clrFinal);

}

//----------------------------------------------------------------------
// Conversion between the HSL (Hue, Saturation, and Luminosity) 
// and RBG color model.
//----------------------------------------------------------------------
// The conversion algorithms presented here come from the book by 
// Fundamentals of Interactive Computer Graphics by Foley and van Dam. 
// In the example code, HSL values are represented as floating point 
// number in the range 0 to 1. RGB tridrants use the Windows convention 
// of 0 to 255 of each element. 
//----------------------------------------------------------------------

double CBCGPDrawManager::HuetoRGB(double m1, double m2, double h )
{
	if( h < 0 ) h += 1.0;
	if( h > 1 ) h -= 1.0;
	if( 6.0*h < 1 )
		return (m1+(m2-m1)*h*6.0);
	if( 2.0*h < 1 )
		return m2;
	if( 3.0*h < 2.0 )
		return (m1+(m2-m1)*((2.0/3.0)-h)*6.0);
	return m1;
}

COLORREF CBCGPDrawManager::HLStoRGB_ONE( double H, double L, double S )
{
	double r, g, b;
	double m1, m2;
	
	if(S==0) {
		r=g=b=L;
	} else {
		if(L <=0.5)
			m2 = L*(1.0+S);
		else
			m2 = L+S-L*S;
		m1 = 2.0*L-m2;
		r = HuetoRGB(m1, m2, H+1.0/3.0);
		g = HuetoRGB(m1, m2, H);
		b = HuetoRGB(m1, m2, H-1.0/3.0);
	}
	return RGB((BYTE)(r*255), (BYTE)(g*255), (BYTE)(b*255));
}

void CBCGPDrawManager::RGBtoHSL( COLORREF rgb, double *H, double *S, double *L )
{   
	double delta;
	double r = (double)GetRValue(rgb)/255;
	double g = (double)GetGValue(rgb)/255;
	double b = (double)GetBValue(rgb)/255;   
	double cmax = max(r, max(g, b));
	double cmin = min(r, min(g, b));   
	*L=(cmax+cmin)/2.0;   
	
	if(cmax==cmin) 
	{
		*S = 0;      
		*H = 0; // it's really undefined   
	} 
	else 
	{
		if(*L < 0.5) 
			*S = (cmax-cmin)/(cmax+cmin);      
		else
			*S = (cmax-cmin)/(2.0-cmax-cmin);      
		
		delta = cmax - cmin;
		if(r==cmax) 
			*H = (g-b)/delta;      
		else if(g==cmax)
			*H = 2.0 +(b-r)/delta;
		else          
			*H=4.0+(r-g)/delta;
		*H /= 6.0; 
		if(*H < 0.0)
			*H += 1;  
	}
}
void CBCGPDrawManager::FillGradient (CRect rect, 
									COLORREF colorStart, COLORREF colorFinish, 
									BOOL bHorz/* = TRUE*/,
									int nStartFlatPercentage/* = 0*/,
									int nEndFlatPercentage/* = 0*/)
{
	if (colorStart == colorFinish)
	{
		CBrush br (colorStart);
		m_dc.FillRect (rect, &br);
		return;
	}

	if (nStartFlatPercentage > 0)
	{
		ASSERT (nStartFlatPercentage <= 100);

		if (bHorz)
		{
			CRect rectTop = rect;
			rectTop.bottom = rectTop.top + 
				rectTop.Height () * nStartFlatPercentage / 100;
			rect.top = rectTop.bottom;

			CBrush br (colorFinish);
			m_dc.FillRect (rectTop, &br);
		}
		else
		{
			CRect rectLeft = rect;
			rectLeft.right = rectLeft.left + 
				rectLeft.Width () * nStartFlatPercentage / 100;
			rect.left = rectLeft.right;

			CBrush br (colorStart);
			m_dc.FillRect (rectLeft, &br);
		}
	}

	if (nEndFlatPercentage > 0)
	{
		ASSERT (nEndFlatPercentage <= 100);

		if (bHorz)
		{
			CRect rectBottom = rect;
			rectBottom.top = rectBottom.bottom - 
				rectBottom.Height () * nEndFlatPercentage / 100;
			rect.bottom = rectBottom.top;

			CBrush br (colorStart);
			m_dc.FillRect (rectBottom, &br);
		}
		else
		{
			CRect rectRight = rect;
			rectRight.left = rectRight.right - 
				rectRight.Width () * nEndFlatPercentage / 100;
			rect.right = rectRight.left;

			CBrush br (colorFinish);
			m_dc.FillRect (rectRight, &br);
		}
	}

	if (nEndFlatPercentage + nStartFlatPercentage > 100)
	{
		ASSERT (FALSE);
		return;
	}

    // this will make 2^6 = 64 fountain steps
    int nShift = 6;
    int nSteps = 1 << nShift;

    for (int i = 0; i < nSteps; i++)
    {
        // do a little alpha blending
        BYTE bR = (BYTE) ((GetRValue(colorStart) * (nSteps - i) +
                   GetRValue(colorFinish) * i) >> nShift);
        BYTE bG = (BYTE) ((GetGValue(colorStart) * (nSteps - i) +
                   GetGValue(colorFinish) * i) >> nShift);
        BYTE bB = (BYTE) ((GetBValue(colorStart) * (nSteps - i) +
                   GetBValue(colorFinish) * i) >> nShift);

		CBrush br (RGB(bR, bG, bB));

        // then paint with the resulting color
        CRect r2 = rect;
        if (bHorz)
        {
            r2.bottom = rect.bottom - 
                ((i * rect.Height()) >> nShift);
            r2.top = rect.bottom - 
                (((i + 1) * rect.Height()) >> nShift);
            if (r2.Height() > 0)
                m_dc.FillRect(r2, &br);
        }
        else
        {
            r2.left = rect.left + 
                ((i * rect.Width()) >> nShift);
            r2.right = rect.left + 
                (((i + 1) * rect.Width()) >> nShift);
            if (r2.Width() > 0)
                m_dc.FillRect(r2, &br);
        }
    }
}
//************************************************************************************
void CBCGPDrawManager::FillGradient2 (CRect rect, COLORREF colorStart, COLORREF colorFinish, 
					int nAngle)
{
	if (colorStart == colorFinish)
	{
		CBrush br (colorStart);
		m_dc.FillRect (rect, &br);
		return;
	}

	//----------------------
	// Process simple cases:
	//----------------------
	switch (nAngle)
	{
	case 0:
	case 360:
		FillGradient (rect, colorStart, colorFinish, FALSE);
		return;

	case 90:
		FillGradient (rect, colorStart, colorFinish, TRUE);
		return;

	case 180:
		FillGradient (rect, colorFinish, colorStart, FALSE);
		return;

	case 270:
		FillGradient (rect, colorFinish, colorStart, TRUE);
		return;
	}

	//--------------------------------------------
	// Copy screen content into the memory bitmap:
	//--------------------------------------------
	CDC dcMem;
	if (!dcMem.CreateCompatibleDC (&m_dc))
	{
		ASSERT (FALSE);
		return;
	}

	CBitmap	bmpMem;
	if (!bmpMem.CreateCompatibleBitmap (&m_dc, rect.Width (), rect.Height ()))
	{
		ASSERT (FALSE);
		return;
	}

	CBitmap* pOldBmp = dcMem.SelectObject (&bmpMem);
	ASSERT (pOldBmp != NULL);

	CPen* pOldPen = (CPen*) dcMem.SelectStockObject (NULL_PEN);

    int nShift = 6;
    int nSteps = 1 << nShift;

	const double fAngle = PI * (nAngle + 180) / 180;
	const int nOffset = (int) (cos (fAngle) * rect.Height ());
	const int nTotalWidth = rect.Width () + abs (nOffset);

	const int xStart = nOffset > 0 ? - nOffset : 0;

    for (int i = 0; i < nSteps; i++)
    {
        // do a little alpha blending
        BYTE bR = (BYTE) ((GetRValue(colorStart) * (nSteps - i) +
                   GetRValue(colorFinish) * i) >> nShift);
        BYTE bG = (BYTE) ((GetGValue(colorStart) * (nSteps - i) +
                   GetGValue(colorFinish) * i) >> nShift);
        BYTE bB = (BYTE) ((GetBValue(colorStart) * (nSteps - i) +
                   GetBValue(colorFinish) * i) >> nShift);

		CBrush br (RGB (bR, bG, bB));

        int x11 = xStart + ((i * nTotalWidth) >> nShift);
        int x12 = xStart + (((i + 1) * nTotalWidth) >> nShift);

		if (x11 == x12)
		{
			continue;
		}

		int x21 = x11 + nOffset;
		int x22 = x21 + (x12 - x11);

		POINT points [4];
		points [0].x = x11;
		points [0].y = 0;
		points [1].x = x12;
		points [1].y = 0;
		points [2].x = x22;
		points [2].y = rect.Height ();
		points [3].x = x21;
		points [3].y = rect.Height ();

		CBrush* pOldBrush = dcMem.SelectObject (&br);
		dcMem.Polygon (points, 4);
		dcMem.SelectObject (pOldBrush);
	}

	dcMem.SelectObject (pOldPen);

	//--------------------------------
	// Copy bitmap back to the screen:
	//--------------------------------
	m_dc.BitBlt (rect.left, rect.top, rect.Width (), rect.Height (), &dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject (pOldBmp);
}
