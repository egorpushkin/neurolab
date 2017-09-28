// InfoHeader.cpp : implementation file
//

#include "stdafx.h"
#include "InfoHeader.h"
#include ".\infoheader.h"


// CInfoHeader

IMPLEMENT_DYNAMIC(CInfoHeader, CWnd)
CInfoHeader::CInfoHeader()
{
	IsOverLink = false;
	pfnOnDraw = NULL;
}

CInfoHeader::~CInfoHeader()
{
}


BEGIN_MESSAGE_MAP(CInfoHeader, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CInfoHeader message handlers


void CInfoHeader::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CGDIPDevice	mGDIDevice;
	Graphics* pGraphics = mGDIDevice.CreateGraphics(&dc);

	CRect ClRect;
	GetClientRect(&ClRect);

	Color	clMainFill(70, 125, 255);
	Color	clBlick(255, 117, 255);
	SolidBrush	brFillMain(clMainFill);
	pGraphics->FillRectangle(&brFillMain, ClRect.left, ClRect.top, ClRect.right, ClRect.bottom-5);

	GraphicsPath path;
	//gclRect	gradRect(CRect(ClRect.left, ClRect.top, ClRect.right, ClRect.bottom-5));
	path.AddEllipse(ClRect.Width()/2, -ClRect.Height()/2, ClRect.Width()/2, ClRect.Height()*1.5);
	PathGradientBrush pthGrBrush(&path);
	//pthGrBrush.SetCenterPoint(Point(ClRect.Width()*2/3, 10));
	pthGrBrush.SetCenterColor(clBlick);
	Color colors[] = {clMainFill};
	int count = 1;
	pthGrBrush.SetSurroundColors(colors, &count);
	pGraphics->FillEllipse(&pthGrBrush, ClRect.Width()/2, -ClRect.Height()/3, ClRect.Width()/2, ClRect.Height()*1.5);

	LinearGradientBrush * brBotBrush = new LinearGradientBrush(
		Point(0, 0),
		Point(ClRect.Width()/2, 0),
		Color(255, 255, 0, 0),   // opaque red
		Color(255, 0, 0, 255));  // opaque blue
	pGraphics->FillRectangle(brBotBrush, 0, ClRect.bottom-5, ClRect.Width()/2, 5);
	delete brBotBrush;

	brBotBrush = new LinearGradientBrush(
		Point(ClRect.Width()/2, 0),
		Point(ClRect.Width(), 0),
		Color(255, 0, 0, 255),
		Color(255, 255, 0, 0)); 
	pGraphics->FillRectangle(brBotBrush, ClRect.Width()/2, ClRect.bottom-5, ClRect.Width(), 5);
	delete brBotBrush;


	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);
	PointF      pointF(5.0f, ClRect.Height()-32);
	SolidBrush  solidBrush(Color(255, 255, 255));
	pGraphics->DrawString(L"© 2004-2005", -1, &font, pointF, &solidBrush);

	pointF = PointF(5.0f, ClRect.Height()-20);
	pGraphics->DrawString(L"Scientific Software", -1, &font, pointF, &solidBrush);

	FontFamily	compnamefontFamily(L"Times New Roman");
	Font		compnamefont(&compnamefontFamily, 18, FontStyleBold, UnitPixel);
	pointF = PointF(ClRect.Width()-155, ClRect.Height()-28);
	pGraphics->DrawString(L"Scientific Software", -1, &compnamefont, pointF, &solidBrush);

	if (pfnOnDraw)
		(*pfnOnDraw)(pGraphics, ClRect);
}

void CInfoHeader::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect ClRect;
	GetClientRect(&ClRect);
	if (point.x > ClRect.Width()-155 && point.y > ClRect.Height()-28)
	{
		HCURSOR hOldCur = SetCursor(LoadCursor(0, MAKEINTRESOURCE(32649)));
		DeleteObject(hOldCur);
		IsOverLink = true;	
	} else
	{
		HCURSOR hOldCur = SetCursor(LoadCursor(0, MAKEINTRESOURCE(IDC_ARROW)));
		DeleteObject(hOldCur);
		IsOverLink = false;	
	}

	CWnd::OnMouseMove(nFlags, point);
}
void CInfoHeader::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (IsOverLink)
	{
		ShellExecute(this->m_hWnd, "Open", "http://www.scientific-soft.com/", "", "c:\\", SW_SHOWMAXIMIZED);
	}

	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CInfoHeader::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}

void CInfoHeader::SetOnDrawHandler(pfnCBInfoHeaderOnDraw OnDraw)
{
	pfnOnDraw = OnDraw;
}

void CInfoHeader::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	UINT nBS;
	nBS = ((CButton *)this)->GetButtonStyle();
	((CButton *)this)->SetButtonStyle(nBS | BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}
