// FuncShowCtrl.cpp : implementation file
//

#include "stdafx.h"

#include "FuncShowCtrl.h"
#include ".\funcshowctrl.h"

//#include "..\OutputLib\GDIPDevice.h" 
// CFuncShowCtrl

IMPLEMENT_DYNAMIC(CFuncShowCtrl, CWnd)
CFuncShowCtrl::CFuncShowCtrl()
	: pDataFactory(NULL)
	, iGrigRange(40)
	, iXOffset(0)
	, iYOffset(0)
	, bIsDragging(false)
	, iCurrentIndex(0)
	, fCurrentValue(0.0f)
{
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

	CRect ClRect;
	GetClientRect(&ClRect);

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

	int	iMark = 1;
	for (int i = iCenterX + iXOffset + iGrigRange;i < ClRect.right;i+=iGrigRange)
	{
		point.X = i + 2;
		point.Y = iCenterY + iYOffset + 2;
		tmText.Format("%d", iMark * 8 - 1);
		pGraphics->DrawString(T2W(tmText), -1, &font, point, &GridMarksBrush);

		pGraphics->DrawLine(&GridPen, i, ClRect.top, i, ClRect.bottom);
		iMark+=iMarkRange;
	}
	
	iMark = -iMarkRange;
	for (int i = iCenterX + iXOffset - iGrigRange;i > ClRect.left;i-=iGrigRange)
	{
		/*point.X = i + 2;
		point.Y = iCenterY + iYOffset - 12;
		tmText.Format("%d", iMark);
		pGraphics->DrawString(T2W(tmText), -1, &font, point, &GridMarksBrush);*/

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
	point.X = iCenterX + iXOffset + 8;
	point.Y = 2;
	tmText = "Value";
	pGraphics->DrawString(T2W(tmText), -1, &AxisFont, point, &AxisBrush);
	point.X = ClRect.right - 35;
	point.Y = iCenterY + iYOffset - 23;
	tmText = "Pos";
	pGraphics->DrawString(T2W(tmText), -1, &AxisFont, point, &AxisBrush);

	// Drawing function
	if (pDataFactory && pDataFactory->GetData() && pDataFactory->GetDataLength() > 0)
	{
		Pen	SignalPen(Color(150, 150, 150), 1);
		Pen	HistogramPen(Color(0, 0, 0), 2);

		int iPrevX = -1;
		int iPrevY = -1;
        
		float iCurrentXOffset = 0;

		for (int i = 0;i < pDataFactory->GetDataLength();i++)
		{
			float tmXTop = iCurrentXOffset / (iGrigRange);
			float tmYTop = pDataFactory->GetItemData(i);

			int	tmCurXTop = (tmXTop*iGrigRange/iMarkRange) + (iCenterX + iXOffset);
			int tmCurYPop = (iCenterY + iYOffset) - (tmYTop*iGrigRange);

			float tmXBottom = tmXTop;
			float tmYBottom = 0;

			int tmCurXBottom = tmCurXTop;
			int tmCurYBottom = (iCenterY + iYOffset);
            		
            pGraphics->DrawLine(&HistogramPen, tmCurXTop, tmCurYPop, tmCurXBottom, tmCurYBottom);		

			if (i > 0)
				pGraphics->DrawLine(&SignalPen, tmCurXTop, tmCurYPop, iPrevX, iPrevY);		

			iPrevX = tmCurXTop;
			iPrevY = tmCurYPop;
		
			iCurrentXOffset += (iGrigRange*1.0f / 8);
		}
	}

	// Drawing Information
	if (pDataFactory && pDataFactory->GetData() && pDataFactory->GetDataLength() > 0)
	{
		USES_CONVERSION;

		SolidBrush ValueBrush(Color(240, 240, 240));
		pGraphics->DrawRectangle(&GridPen, ClRect.right - 80, 3, 77, 28);
		pGraphics->FillRectangle(&ValueBrush, ClRect.right - 79, 5, 76, 26);

		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 11, FontStyleBold, UnitPixel);
		PointF      point(ClRect.right - 80, 4);
		SolidBrush  ValueFontBrush(Color(0, 0, 0));

		CString tmValue;
		tmValue.Format("Ind: %d", iCurrentIndex);
		pGraphics->DrawString(T2W(tmValue), -1, &font, point, &ValueFontBrush);

		point = PointF(ClRect.right - 80, 17);
		tmValue.Format("Val: %0.4f", fCurrentValue);
		pGraphics->DrawString(T2W(tmValue), -1, &font, point, &ValueFontBrush);

	}
}

void CFuncShowCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bIsDragging = true;
	PrevDragPosition = point;

	CWnd::OnLButtonDown(nFlags, point);
}

void CFuncShowCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bIsDragging = false;
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CFuncShowCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();

	CPoint tmPoint = point;
	ClientToScreen(&tmPoint);
    CWnd* wndUnderMouse = WindowFromPoint(tmPoint);
	if (wndUnderMouse != this && !bIsDragging)
	{		
		GetOwner()->SetFocus();
		ReleaseCapture();
		return;
	}

	if (bIsDragging)
	{
		iXOffset += (point.x - PrevDragPosition.x);
		iYOffset += (point.y - PrevDragPosition.y);

		PrevDragPosition = point;
		Invalidate();
	}

	UpdateCurrentValues(point);

	CWnd::OnMouseMove(nFlags, point);
}

void CFuncShowCtrl::UpdateCurrentValues(CPoint& point)
{
	if (pDataFactory)
	{
		CRect ClRect;
		GetClientRect(&ClRect);

		int iCenterX = ClRect.Width()/2;

		int tmIndex = (point.x - iCenterX - iXOffset + iGrigRange/16)*8/iGrigRange;
		if (tmIndex >= 0 && tmIndex < pDataFactory->GetDataLength())
		{
			iCurrentIndex = tmIndex;
			fCurrentValue = pDataFactory->GetItemData(tmIndex);
		
			Invalidate();
		}		
	}
}