// FuncShowCtrl.cpp : implementation file
//

#include "stdafx.h"

#include "FuncShowCtrl.h"
#include ".\funcshowctrl.h"

//#include "..\OutputLib\GDIPDevice.h" 
// CFuncShowCtrl

IMPLEMENT_DYNAMIC(CFuncShowCtrl, CWnd)
CFuncShowCtrl::CFuncShowCtrl()
{
	pfnFunction = NULL;

	iXOffset = 0;
	iYOffset = 0;

	bIsDragging = false;

	iGrigRange = 40;

	FunctionParam = NULL;
}

CFuncShowCtrl::~CFuncShowCtrl()
{
}


BEGIN_MESSAGE_MAP(CFuncShowCtrl, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CFuncShowCtrl message handlers


BOOL CFuncShowCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;//CWnd::OnEraseBkgnd(pDC);
}

void CFuncShowCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages


/*	CMemDC	MemDC(&dc);

	gclRenderStruct r;*/
	CRect ClRect;
	GetClientRect(&ClRect);

//	GCLInitRenderStruct(&r,MemDC);*/

	CGDIPDevice	mGDIDevice;
	Graphics* pGraphics = mGDIDevice.CreateGraphics(&dc);

	SolidBrush	BackGroundBrush(Color(224, 223, 227));
	pGraphics->FillRectangle(&BackGroundBrush, ClRect.left, ClRect.top,
		ClRect.Width(), ClRect.Height());

	// Drawing datum lines	
	int iCenterX = ClRect.Width()/2;
	int iCenterY = ClRect.Height()/2;

	Pen	DatumsPen(Color(0, 0, 0), 2);
	pGraphics->DrawLine(&DatumsPen, iCenterX + iXOffset, ClRect.top, 
		iCenterX + iXOffset, ClRect.bottom);
	pGraphics->DrawLine(&DatumsPen, iCenterX + iXOffset, ClRect.top, 
		iCenterX + iXOffset - 5, ClRect.top + 15);
	pGraphics->DrawLine(&DatumsPen, iCenterX + iXOffset, ClRect.top, 
		iCenterX + iXOffset + 5, ClRect.top + 15);

	pGraphics->DrawLine(&DatumsPen, ClRect.left, iCenterY + iYOffset, 
		ClRect.right, iCenterY + iYOffset);	
	pGraphics->DrawLine(&DatumsPen, ClRect.right - 15, iCenterY + iYOffset - 5, 
		ClRect.right, iCenterY + iYOffset);
	pGraphics->DrawLine(&DatumsPen, ClRect.right - 15, iCenterY + iYOffset + 5, 
		ClRect.right, iCenterY + iYOffset);

	// Drawing some grid 
	Pen	GridPen(Color(150, 150, 150), 1);

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);
	PointF      point;
	SolidBrush  GridMarksBrush(Color(100, 100, 100));
//	pGraphics->DrawString(T2W(tmBarText), -1, &font, point, &TitleUnderBrush);

	int	iMarkRange = 1;

	CString	tmText;
	USES_CONVERSION;

	int	iMark = iMarkRange;
	for (int i = iCenterX + iXOffset + iGrigRange;i < ClRect.right;i+=iGrigRange)
	{
		point.X = i + 2;
		point.Y = iCenterY + iYOffset + 2;
		tmText.Format("%d", iMark);
		pGraphics->DrawString(T2W(tmText), -1, &font, point, &GridMarksBrush);

		pGraphics->DrawLine(&GridPen, i, ClRect.top, i, ClRect.bottom);
		iMark+=iMarkRange;
	}
	
	iMark = -iMarkRange;
	for (int i = iCenterX + iXOffset - iGrigRange;i > ClRect.left;i-=iGrigRange)
	{
		point.X = i + 2;
		point.Y = iCenterY + iYOffset - 12;
		tmText.Format("%d", iMark);
		pGraphics->DrawString(T2W(tmText), -1, &font, point, &GridMarksBrush);

		pGraphics->DrawLine(&GridPen, i, ClRect.top, i, ClRect.bottom);
		iMark -= iMarkRange;
	}

	iMark = -iMarkRange;
	for (int j = iCenterY + iYOffset + iGrigRange;j < ClRect.bottom;j+=iGrigRange)
	{
		point.X = iCenterX + iXOffset - 18;
		point.Y = j - 12;
		tmText.Format("%d", iMark);
		pGraphics->DrawString(T2W(tmText), -1, &font, point, &GridMarksBrush);

		pGraphics->DrawLine(&GridPen, ClRect.left, j, ClRect.right, j);
		iMark -= iMarkRange;
	}

	iMark = iMarkRange;
	for (int j = iCenterY + iYOffset - iGrigRange;j > ClRect.top;j-=iGrigRange)
	{
		point.X = iCenterX + iXOffset + 2;
		point.Y = j - 12;
		tmText.Format("%d", iMark);
		pGraphics->DrawString(T2W(tmText), -1, &font, point, &GridMarksBrush);

		pGraphics->DrawLine(&GridPen, ClRect.left, j, ClRect.right, j);
		iMark += iMarkRange;
	}

	Font        AxisFont(&fontFamily, 18, FontStyleRegular, UnitPixel);
	SolidBrush  AxisBrush(Color(50, 50, 50));
	point.X = iCenterX + iXOffset - 23;
	point.Y = 2;
	tmText = "Y";
	pGraphics->DrawString(T2W(tmText), -1, &AxisFont, point, &AxisBrush);
	point.X = ClRect.right - 20;
	point.Y = iCenterY + iYOffset - 23;
	tmText = "X";
	pGraphics->DrawString(T2W(tmText), -1, &AxisFont, point, &AxisBrush);

	// Drawing function
	if (pfnFunction)
	{
		Pen	FunctionPen(Color(51, 35, 248), 1);

		int	iPrevX = 0;
		int iPrevY = iCenterY + iYOffset;
		for (int i = ClRect.left;i<=ClRect.right;i+=1)
		{
			float tmX = ((-1.0*(iCenterX + iXOffset - i))/(iGrigRange*1.0))*(iMarkRange*1.0);
			float tmY = (*pfnFunction)(FunctionParam, tmX);

			int	iCurX = (tmX*iGrigRange/iMarkRange) + (iCenterX + iXOffset);
			int	iCurY = (iCenterY + iYOffset) - (tmY*iGrigRange/iMarkRange);

			pGraphics->DrawLine(&FunctionPen, iPrevX, iPrevY, iCurX, iCurY);            

			iPrevX = iCurX;
			iPrevY = iCurY;
		}


	}
}

void CFuncShowCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bIsDragging = true;
	SetCapture();
	PrevDragPosition = point;

	CWnd::OnLButtonDown(nFlags, point);
}

void CFuncShowCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bIsDragging = false;
	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CFuncShowCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bIsDragging)
	{
		iXOffset += (point.x - PrevDragPosition.x);
		iYOffset += (point.y - PrevDragPosition.y);

		PrevDragPosition = point;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}
