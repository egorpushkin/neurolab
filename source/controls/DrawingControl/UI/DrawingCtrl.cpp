#include "Common/stdafx.h"

#include "DrawingCtrl.h"
#include ".\drawingctrl.h"

namespace DrawingControl
{

	DrawingCtrl::DrawingCtrl()
		: CWnd()
		, dragging_(false)
		, prevPosition_()
		, events_()
	{
	}

	DrawingCtrl::~DrawingCtrl()
	{

	}

	BEGIN_MESSAGE_MAP(DrawingCtrl, CWnd)
		ON_WM_PAINT()
		ON_WM_SIZE()
		ON_WM_MOUSEWHEEL()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_ERASEBKGND()
		ON_WM_TIMER()
	END_MESSAGE_MAP()

	BOOL DrawingCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
	{
		BOOL ret = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

		if ( ret )
		{
			CRect rect;
			GetClientRect(&rect);			
		}

		return ret;
	}

	void DrawingCtrl::OnPaint()
	{
		// Get area info
		CRect rect;
		GetClientRect(&rect);

		// Construct basic GDI devices
		CPaintDC dc(this);

		// Initiate double buffering via GDI+
		Gdiplus::Graphics* pSourceDevice = new Gdiplus::Graphics(dc.m_hDC);
		Gdiplus::Bitmap* pBufferBitmap = new Gdiplus::Bitmap(rect.right, rect.bottom);
		Gdiplus::Graphics* pBufferDevice = Gdiplus::Graphics::FromImage(pBufferBitmap);

		// Draw control
		if ( events_ )
			events_->OnPaint(pBufferDevice);

		// Dump buffer context to display
		pSourceDevice->DrawImage(pBufferBitmap, rect.left, rect.top, rect.right, rect.bottom);

		delete pBufferDevice;
		delete pBufferBitmap;
		delete pSourceDevice;
	}

	void DrawingCtrl::OnSize(UINT nType, int cx, int cy)
	{
		CWnd::OnSize(nType, cx, cy);

		if ( events_ )
			events_->OnSize(nType, cx, cy);
	}

	BOOL DrawingCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
	{
		if ( events_ )
			events_->OnMouseWheel(nFlags, zDelta, point);

		Invalidate();

		return CWnd::OnMouseWheel(nFlags, zDelta, point);
	}

	void DrawingCtrl::OnLButtonDown(UINT nFlags, CPoint point)
	{
		SetFocus();
		SetCapture();

		if ( events_ )
			events_->OnLButtonDown(nFlags, point);

		CWnd::OnLButtonDown(nFlags, point);
	}

	void DrawingCtrl::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if ( events_ )
			events_->OnLButtonUp(nFlags, point);

		ReleaseCapture();

		CWnd::OnLButtonUp(nFlags, point);
	}

	void DrawingCtrl::OnMouseMove(UINT nFlags, CPoint point)
	{
		if ( events_ )
			events_->OnMouseMove(nFlags, point);

		CWnd::OnMouseMove(nFlags, point);
	}

	void DrawingControl::DrawingCtrl::OnTimer(UINT nIDEvent)
	{
		if ( events_ )
			events_->OnTimer(nIDEvent);	

		CWnd::OnTimer(nIDEvent);
	}

	BOOL DrawingCtrl::OnEraseBkgnd(CDC* /* pDC */)
	{
		return FALSE; // CWnd::OnEraseBkgnd(pDC);
	}

	// IDrawingControl section
	result DrawingCtrl::Create(CWnd* pParent, const CRect& rect)
	{
		BOOL crRet = CWnd::Create(NULL, "", WS_CHILD | WS_VISIBLE, rect, pParent, IDC_DRAWING_CTRL);

		if ( crRet )
		{
			if ( events_ )
				events_->OnInit();
		}

		return ( crRet ) ? 
			( S_OK ) : ( E_FAIL );
	}

	result DrawingCtrl::Move(const CRect& rect)
	{
		if ( m_hWnd )
		{
			CWnd::MoveWindow(&rect);
		}

		return S_OK;
	}

	result DrawingCtrl::SetEventsHandler(IEvents* events)
	{
		events_ = IEventsPtr(events, IID_IEvents);		
		return S_OK;
	}

	void DrawingCtrl::SetTimer(uint id, dword elapse)
	{
		if ( !m_hWnd )
			return;

		CWnd::SetTimer(id, elapse, NULL);
	}

	void DrawingCtrl::KillTimer(uint id)
	{
		if ( !m_hWnd )
			return;

		CWnd::KillTimer(id);
	}

	void DrawingCtrl::Repaint()
	{
		if ( !m_hWnd )
			return;

		Invalidate();
	}

	// ICommon section
	result DrawingCtrl::QueryInterface(REFIID iid, void** ppObject)
	{
		if ( iid == MinCOM::IID_ICommon )
			*ppObject = static_cast< MinCOM::ICommon* >(this);

		else if ( iid == IID_IDrawingControl )
			*ppObject = static_cast< IDrawingControl* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		static_cast< MinCOM::ICommon* >(this)->AddRef();
		return S_OK;
	}

} // Simple2dCharting
