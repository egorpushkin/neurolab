#include "Common/Includes.h"

#include "Cartesian/Cartesian.h"

#include "Common/BasicDevice.h"

#include "Common/BasicChart.h"

#include "Common/BasicLocator.h"

#include "Common/BasicRenderer.h"

#include "Common/BasicManipulator.h"

#include "Common/ChartTool.h"

#include "Common/BasicControl.h"

#ifndef WINVER				
#define WINVER 0x0400		
#endif

#include <afxwin.h> 
#include <afxext.h>  

#include "ChartCwndCtrl.h"

#include <gdiplus.h>
#include "Devices/GDIPDevice.h"

#include "Common/DeviceHolder.h"

namespace Simple2dCharting
{

	ChartCwndCtrl::ChartCwndCtrl()
		: CWnd()
		, BasicControl(BasicDevicePtr(new GdipDevice))		
		, dragging_(false)
		, prevPosition_()
	{
	}

	ChartCwndCtrl::~ChartCwndCtrl()
	{

	}

	BEGIN_MESSAGE_MAP(ChartCwndCtrl, CWnd)
		ON_WM_PAINT()
		ON_WM_SIZE()
		ON_WM_MOUSEWHEEL()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_ERASEBKGND()
	END_MESSAGE_MAP()

	BOOL ChartCwndCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
	{
		BOOL ret = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

		if ( ret )
		{
			CRect rect;
			GetClientRect(&rect);			

			BasicControl::cartesians_->SetWidth((float)rect.Width());
			BasicControl::cartesians_->SetHeight((float)rect.Height());

			BasicControl::cartesians_->SetX((float)rect.Width() / 2.0f);
			BasicControl::cartesians_->SetY((float)rect.Height() / 2.0f);
		}

		return ret;
	}

	void ChartCwndCtrl::OnPaint()
	{
		CPaintDC dc(this);
		
		DeviceHolder devHolder(BasicControl::device_, m_hWnd, dc.m_hDC);

		BasicControl::RenderCharts();		
	}

	void ChartCwndCtrl::OnSize(UINT nType, int cx, int cy)
	{
		CWnd::OnSize(nType, cx, cy);

		BasicControl::cartesians_->SetWidth((float)cx);
		BasicControl::cartesians_->SetWidth((float)cy);
	}

	BOOL ChartCwndCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		if ( zDelta > 0 )
			BasicControl::manipulator_->ZoomIn();
		else
			BasicControl::manipulator_->ZoomOut();

		Invalidate();

		return CWnd::OnMouseWheel(nFlags, zDelta, pt);
	}

	void ChartCwndCtrl::OnLButtonDown(UINT nFlags, CPoint point)
	{
		SetFocus();

		SetCapture();
		dragging_ = true;
		prevPosition_ = point;

		CWnd::OnLButtonDown(nFlags, point);
	}

	void ChartCwndCtrl::OnLButtonUp(UINT nFlags, CPoint point)
	{
		dragging_ = false;
		ReleaseCapture();

		CWnd::OnLButtonUp(nFlags, point);
	}

	void ChartCwndCtrl::OnMouseMove(UINT nFlags, CPoint point)
	{
		if ( dragging_ )
		{
			BasicControl::manipulator_->MoveViewport(
				(float)point.x - prevPosition_.x,
				(float)point.y - prevPosition_.y
			);

			prevPosition_ = point;

			Invalidate();
		}

		CWnd::OnMouseMove(nFlags, point);
	}


	BOOL ChartCwndCtrl::OnEraseBkgnd(CDC* /* pDC */)
	{
		return FALSE; // CWnd::OnEraseBkgnd(pDC);
	}

} // Simple2dCharting

