// InfoBar.cpp : implementation file
//

#include "stdafx.h"

#include "InfoBar.h"
#include ".\infobar.h"

#include "..\\Resource.h"

#define IB_CTRL_RIGHTPANEL_WIDTH		11

#define IB_SUBCTRL_TOOLTIP				1
#define IB_SUBCTRL_RIGHTPANEL			2
#define IB_SUBCTRL_DRAGGINGPANEL		3

#define IB_TOOLTIPID					1
#define IB_TOOLTIPRIGHTPANELID			2

// CInfoBar

IMPLEMENT_DYNAMIC(CInfoBar, CWnd)
CInfoBar::CInfoBar()
{
	bToolTipEnabled = false;
	bToolAdded = false;

	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);

	bIsOverRightPanel = false;
	bIsMenuInitialized = false;
	bPopupToolAdded = false;
	bPopupToolTipEnabled = false;

	bIsDraggingEnabled = false;
	bIsDragging = false;

	iUnderCursorSubCtrlID = -1;

	csMediaDirectory = "Images";
}

CInfoBar::~CInfoBar()
{
}


BEGIN_MESSAGE_MAP(CInfoBar, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CInfoBar message handlers


BOOL CInfoBar::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;//CWnd::OnEraseBkgnd(pDC);
}

void CInfoBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CRect ClRect;
	GetClientRect(&ClRect);

	CGDIPDevice	mGDIDevice;
	Graphics* pGraphics = mGDIDevice.CreateGraphics(&dc);	

	// Drawing right panel
	Color	PanelTopGradColor(117, 166, 241);
	Color	PanelBottomGradColor(6, 59, 150);

	if (bIsOverRightPanel)
	{
		PanelTopGradColor.SetFromCOLORREF(RGB(255, 248, 211));
		PanelBottomGradColor.SetFromCOLORREF(RGB(255, 193, 118));	
	}
	
	LinearGradientBrush PanelGradBrush(
		Point(0, -1),
		Point(0, ClRect.bottom+1),
		PanelTopGradColor,   
		PanelBottomGradColor);

	HRGN hRgn = CreateRoundRectRgn(
		ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5, 0, ClRect.right+1, ClRect.bottom+1, 
		5, 5);
	Region PanelRegion(hRgn);
	DeleteObject(hRgn);

	pGraphics->FillRegion(&PanelGradBrush, &PanelRegion);

	// Drawing push button on the right panel
	Pen		BlackPen(Color::Black);
	Pen		WhitePen(Color::White);
    
	pGraphics->DrawLine(&BlackPen, ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 8,
		ClRect.top + 14,
		ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 12, 
		ClRect.top + 14);
	pGraphics->DrawLine(&WhitePen, ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 9,
		ClRect.top + 15, 
		ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 13, 
		ClRect.top + 15);

	SolidBrush	WhiteBrush(Color::White);	
	SolidBrush	BlackBrush(Color::Black);	
	
	GraphicsPath	WhiteTrianglePath;
	GraphicsPath	BlackTrianglePath;

	WhiteTrianglePath.AddLine(ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 9,
			ClRect.top + 15 + 3,
			ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 14,
			ClRect.top + 15 + 3);
	WhiteTrianglePath.AddLine(ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 14,
			ClRect.top + 15 + 3,
			ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 11,
			ClRect.top + 15 + 6);
	WhiteTrianglePath.AddLine(ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 11,
			ClRect.top + 15 + 6,
			ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 9,
			ClRect.top + 15 + 3);

	BlackTrianglePath.AddLine(ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 8,
			ClRect.top + 14 + 3,
			ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 13,
			ClRect.top + 14 + 3);
	BlackTrianglePath.AddLine(ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 13,
			ClRect.top + 14 + 3,
			ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 10,
			ClRect.top + 14 + 6);
	BlackTrianglePath.AddLine(ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 10,
			ClRect.top + 14 + 6,
			ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH - 5 + 8,
			ClRect.top + 14 + 3);
	
	Region			WhiteTriangleRgn(&WhiteTrianglePath);
	Region			BlackTriangleRgn(&BlackTrianglePath);

	pGraphics->FillRegion(&WhiteBrush, &WhiteTriangleRgn);
	pGraphics->FillRegion(&BlackBrush, &BlackTriangleRgn);

	// Drawing background using gradient fill
	Color	BarTopGradColor(221, 236, 254);
	Color	BarBottomGradColor(129, 169, 226);
	
	LinearGradientBrush GradBrush(
		Point(0, -1),
		Point(0, ClRect.bottom+1),
		BarTopGradColor,   
		BarBottomGradColor);

	hRgn = CreateRoundRectRgn(
		0, 0, ClRect.right-IB_CTRL_RIGHTPANEL_WIDTH+1, ClRect.bottom+1, 
		5, 5);
	Region BackGroundRegion(hRgn);
	DeleteObject(hRgn);

	pGraphics->FillRegion(&GradBrush, &BackGroundRegion);

	// Drawing points column
	Color	LeftPointOverColor(39, 65, 118);
	Color	LeftPointUnderColor(255, 255, 255);

	SolidBrush LeftPointOverBrush(LeftPointOverColor);
	SolidBrush LeftPointUnderBrush(LeftPointUnderColor);	
	
	int tmX = 3;
	int tmY = 4;
	for (int i = 0;i<4;i++)
	{	
		pGraphics->FillRectangle(&LeftPointUnderBrush, 
			tmX+1, tmY+1, 2, 2);
		pGraphics->FillRectangle(&LeftPointOverBrush, 
			tmX, tmY, 2, 2);		
		tmY += 4;
	}

	// Drawing bottom line
	Color	BarBottomLineColor(59, 97, 156);
	Pen		BottomLinePen(BarBottomLineColor);
	pGraphics->DrawLine(&BottomLinePen, ClRect.left+2, ClRect.bottom-1, ClRect.right - IB_CTRL_RIGHTPANEL_WIDTH - 3, ClRect.bottom-1);

	// Drawing bar title
	CString		tmBarText;
	GetWindowText(tmBarText);

	USES_CONVERSION;

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 15, FontStyleBold, UnitPixel);
	PointF      point(11, 4);
	SolidBrush  TitleUnderBrush(Color(255, 255, 255));
	SolidBrush  TitleOverBrush(Color(112, 43, 112));
	pGraphics->DrawString(T2W(tmBarText), -1, &font, point, &TitleUnderBrush);
	point.X--;
	point.Y--;
	pGraphics->DrawString(T2W(tmBarText), -1, &font, point, &TitleOverBrush);

	if (bToolTipEnabled)
	{
		Image		QuestionImage(T2W(csAppFolder + CString("\\") + csMediaDirectory + CString("\\ToolButton.gif")));
		pGraphics->DrawImage(&QuestionImage, ClRect.right - 35, 3);
	}
}

void CInfoBar::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	//CWnd::PreSubclassWindow();
}

void CInfoBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pParent = GetOwner();

	if (bIsDragging)
	{
		CRect	ClRect;
		GetClientRect(&ClRect);

		ClientToScreen(&ClRect);
		pParent->ScreenToClient(&ClRect);

		int tmXDiff = (point.x - pntPrevDrag.x) - 1;
		int tmYDiff = (point.y - pntPrevDrag.y) - 1;

		ClRect.OffsetRect(tmXDiff, tmYDiff);

		MoveWindow(ClRect);

		CWnd::OnMouseMove(nFlags, point);
		return;
	}
	
	bool	bIsArrow = true;
	if (bIsDraggingEnabled)
		if (IsOverDragPanel(point))
		{
			if (iUnderCursorSubCtrlID != IB_SUBCTRL_DRAGGINGPANEL)
			{
				HCURSOR hOldCur = SetCursor(LoadCursor(0, MAKEINTRESOURCE(IDC_SIZEALL)));
				DeleteObject(hOldCur);			
				iUnderCursorSubCtrlID = IB_SUBCTRL_DRAGGINGPANEL;
			}
			bIsArrow = false;
		}
	if (bToolTipEnabled)
		if (IsOverToolTip(point))
		{
			if (iUnderCursorSubCtrlID != IB_SUBCTRL_TOOLTIP)
			{
				HCURSOR hOldCur = SetCursor(LoadCursor(0, MAKEINTRESOURCE(32649)));
				DeleteObject(hOldCur);			
				iUnderCursorSubCtrlID = IB_SUBCTRL_TOOLTIP;
			}
			bIsArrow = false;
		}
	if (bIsArrow)
	{
		HCURSOR hOldCur = SetCursor(LoadCursor(0, MAKEINTRESOURCE(IDC_ARROW)));
		DeleteObject(hOldCur);			
		iUnderCursorSubCtrlID = -1;
	}

	bool	tmOverCtrl = IsOverRightPanel(point);
	if (bIsOverRightPanel != tmOverCtrl)
	{
		bIsOverRightPanel = tmOverCtrl;
		Invalidate();
	}

	if ((GetCapture() != this) && (pParent != NULL)) 
	{
		SetCapture();
	} 
	else
	{
		POINT tmPoint = point;
		ClientToScreen(&tmPoint);
		CWnd* wndUnderMouse = WindowFromPoint(tmPoint);
		if (wndUnderMouse != this)
		{
			if (bIsOverRightPanel == TRUE)
			{
				bIsOverRightPanel = FALSE;
				Invalidate();
			}
			iUnderCursorSubCtrlID = -1;
			ReleaseCapture();
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

int CInfoBar::GetSubControlID(CPoint& point)
{
	if (IsOverToolTip(point))
		return IB_SUBCTRL_TOOLTIP;

	return 0;
}

void CInfoBar::InitToolTips(int iTTMaxWidth)
{
	if (!bToolTipEnabled)
	{
		bToolTipEnabled = true;		
		BOOL bResult = mToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | 0x40);
		mToolTip.Activate(FALSE);
		mToolTip.SetMaxTipWidth(iTTMaxWidth);
	}
}

void CInfoBar::SetToolTipText(CString& text, CString& title)
{
	InitToolTips();

	if (!bToolAdded)
	{
		CRect	ClRect;
		GetClientRect(&ClRect);

		ClRect.left = ClRect.right - 40;
		ClRect.right = ClRect.right - 40 + 18 - 1;
		ClRect.top = 3;
		ClRect.bottom = 3 + 18 - 1;

		BOOL bResult = mToolTip.AddTool(this, text, &ClRect, IB_TOOLTIPID);

		bToolAdded = true;
	}
	//}

	mToolTip.UpdateTipText(text, this, IB_TOOLTIPID);

	if (title.GetLength()>1)
	{
		::SendMessage(mToolTip.m_hWnd, (WM_USER + 32), 1/*info icon*/, (LPARAM)(LPCTSTR)title);		
	}

	mToolTip.Activate(TRUE);
}

bool CInfoBar::IsOverToolTip(CPoint& point)
{
	CRect ClRect;
	GetClientRect(&ClRect);

	if (point.x >= ClRect.right - 40 && point.x < ClRect.right - 40 + 18 &&
		point.y >= 3 && point.y < 3 + 18)
		return true;
	return false;
}

bool CInfoBar::IsOverRightPanel(CPoint& point)
{
	CRect ClRect;
	GetClientRect(&ClRect);

	if (point.x >= ClRect.right - IB_CTRL_RIGHTPANEL_WIDTH)
		return true;
	return false;
}

BOOL CInfoBar::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->message== WM_LBUTTONDOWN ||
        pMsg->message== WM_LBUTTONUP ||
        pMsg->message== WM_MOUSEMOVE))
	{
		if (bToolTipEnabled)
			mToolTip.RelayEvent(pMsg);
		if (bPopupToolTipEnabled)
			mPopupToolTip.RelayEvent(pMsg);
	}

	return CWnd::PreTranslateMessage(pMsg);
}
void CInfoBar::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	if (bIsOverRightPanel)
	{
		bIsOverRightPanel = false;
		Invalidate();
	}

	// TODO: Add your message handler code here
}

void CInfoBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bIsDraggingEnabled)
		if (IsOverDragPanel(point))
		{
			bIsDragging = true;
			pntPrevDrag = point;
			SetCapture();
	
			CRect	ClRect;
			GetClientRect(&ClRect);
			CRect	tmCursorRect(DraggingRect.left + point.x,
				DraggingRect.top + point.y,
				DraggingRect.right - (ClRect.Width() - point.x) + 1,
				DraggingRect.bottom - (ClRect.Height() - point.y) + 1);
			GetParent()->ClientToScreen(&tmCursorRect);

			ClipCursor(&tmCursorRect);
		}

	CWnd::OnLButtonDown(nFlags, point);
}

void CInfoBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bIsDraggingEnabled)
		if (bIsDragging)
		{
			bIsDragging = false;
			ReleaseCapture();
			
			ClipCursor(NULL);
		}

	if (bIsOverRightPanel)
	{
		if (bIsMenuInitialized)
		{
			CPoint	tmMenuPos = point;
			ClientToScreen(&tmMenuPos);				

			CMenu * mPopup = mBarPopupMenu.GetSubMenu(iSubMenu);
			if (mPopup)
			{
				mPopup->TrackPopupMenu(
					TPM_LEFTALIGN|TPM_LEFTBUTTON,
					tmMenuPos.x, tmMenuPos.y, this);

				bIsOverRightPanel = false;
				Invalidate();
			}
		}
	}
    
	CWnd::OnLButtonUp(nFlags, point);
}

void CInfoBar::SetDragParameters(CRect * rect)
{
	if (rect)
	{
		bIsDraggingEnabled = true;
		DraggingRect = *rect;	
	} else
	{
		bIsDraggingEnabled = false;
	}
}

void CInfoBar::SetBarPopupMenu(int MenuResourceID, int SubMenuID)
{
	if (bIsMenuInitialized)
		mBarPopupMenu.DestroyMenu();
	if (mBarPopupMenu.LoadMenu(MenuResourceID))
	{
		iSubMenu = SubMenuID;
		bIsMenuInitialized = true;
	}
}

void CInfoBar::SetRightPanelTips(CString& text, int iTTMaxWidth)
{
	if (!bPopupToolTipEnabled)
	{
		mPopupToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX);
		mPopupToolTip.Activate(TRUE);
		mPopupToolTip.SetMaxTipWidth(iTTMaxWidth);
	
		bPopupToolTipEnabled = true;
	}

	if (!bPopupToolAdded)
	{
		CRect	ClRect;
		GetClientRect(&ClRect);

		ClRect.left = ClRect.right - IB_CTRL_RIGHTPANEL_WIDTH;

		mPopupToolTip.AddTool(this, text, &ClRect, IB_TOOLTIPRIGHTPANELID);
		bPopupToolAdded = true;
	}

	mPopupToolTip.UpdateTipText(text, this, IB_TOOLTIPRIGHTPANELID);
}

bool CInfoBar::IsOverDragPanel(CPoint & point)
{
	if (point.x <= 7)
		return true;
	return false;
}

void CInfoBar::UpdateToolTips()
{
	if (bToolAdded)
	{
		CRect	ClRect;
		GetClientRect(&ClRect);

		ClRect.left = ClRect.right - 40;
		ClRect.right = ClRect.right - 40 + 18 - 1;
		ClRect.top = 3;
		ClRect.bottom = 3 + 18 - 1;

		mToolTip.SetToolRect(this, IB_TOOLTIPID, &ClRect);
	}

	if (bPopupToolAdded)
	{
		CRect	ClRect;
		GetClientRect(&ClRect);

		ClRect.left = ClRect.right - IB_CTRL_RIGHTPANEL_WIDTH;

		mPopupToolTip.SetToolRect(this, IB_TOOLTIPRIGHTPANELID, &ClRect);
	}
	
}
void CInfoBar::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	UpdateToolTips();

	// TODO: Add your message handler code here
}

void CInfoBar::SetMediaDirectory(CString& Directory)
{
	csMediaDirectory = Directory;
}