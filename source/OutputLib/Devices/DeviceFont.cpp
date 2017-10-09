#include "StdAfx.h"
#include "DeviceFont.h"

#include "interface_idds.h"

CDeviceFont::CDeviceFont(HDC hDC, int Height, float r, float g, float b)
{
	glDisplayList = NULL;

	iFontHeight = Height;

	SetColor(r, g, b);

	BuildFont(hDC);
}

CDeviceFont::~CDeviceFont()
{
	KillFont();
}

void CDeviceFont::SetColor(float r, float g, float b)
{
	fRed = r;
	fGreen = g;
	fBlue = b;
}

void CDeviceFont::BuildFont(HDC hDC)						
{
	if (glDisplayList)
		KillFont();
		
	HFONT	fntNewFont;										
	HFONT	fntOldfont;		
	
	glDisplayList = glGenLists(96);								

	fntNewFont = ::CreateFont(
		-abs(iFontHeight),				// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_BOLD,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
		"Times New Roman");				// Font Name

	fntOldfont = (HFONT)::SelectObject(hDC, fntNewFont);         
	wglUseFontBitmaps(hDC, 32, 96, glDisplayList);
	SelectObject(hDC, fntOldfont);
	DeleteObject(fntNewFont);		
}

void CDeviceFont::KillFont(void)									
{
	if (glDisplayList)
	{
		glDeleteLists(glDisplayList, 96);
		glDisplayList = NULL;
	}
}

// IDeviceFont implementations section
void CDeviceFont::RenderString(CString& String, float xPos, float yPos, IDeviceDriver* pDriver)
{
    glColor3f(fRed, fGreen, fBlue);
	pDriver->RasterPos2f(xPos, yPos);

	glPushAttrib(GL_LIST_BIT);	
	glListBase(glDisplayList - 32);		
	glCallLists(String.GetLength(), GL_UNSIGNED_BYTE, (LPCTSTR)String);
	glPopAttrib();	
}

// IObject implementations section
CString CDeviceFont::GetClassString()
{
	return _T("CDeviceFont");
}

void CDeviceFont::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IDeviceFont:
		*ppvObject = (IDeviceFont*)this;
		break;
	}
}