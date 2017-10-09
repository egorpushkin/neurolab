#ifndef DRAWINGCTRL_H__DRAWINGCONTROL__INCLUDED_
#define DRAWINGCTRL_H__DRAWINGCONTROL__INCLUDED_

namespace DrawingControl
{

	class DrawingCtrl 
		: public CWnd
		, public MinCOM::CommonImpl< IDrawingControl >
	{
	public:

		DrawingCtrl();
		virtual ~DrawingCtrl();

		// IDrawingControl section
		virtual result Create(CWnd* pParent, const CRect& rect);
		virtual result Move(const CRect& rect);

		virtual result SetEventsHandler(IEvents* events);

		virtual void SetTimer(uint id, dword elapse);
		virtual void KillTimer(uint id);

		virtual void Repaint();

		// ICommon section
		virtual result QueryInterface(REFIID iid, void** ppObject);

	protected:

		DECLARE_MESSAGE_MAP()

	private:

		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	public:

		virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	private:

		bool dragging_;
		CPoint prevPosition_;

		IEventsPtr events_;

	public:
		afx_msg void OnTimer(UINT nIDEvent);
	};

} // Simple2dCharting

#endif // !DRAWINGCTRL_H__DRAWINGCONTROL__INCLUDED_
