#ifndef CHARTCWNDCTRL_H__S2DCHARTING__INCLUDED_
#define CHARTCWNDCTRL_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class ChartCwndCtrl 
		: public CWnd
		, public BasicControl
	{
	public:
		ChartCwndCtrl();
		virtual ~ChartCwndCtrl();

		// Public interface
		
		
		


	private:
	
		bool dragging_;
		CPoint prevPosition_;
		




	protected:

		DECLARE_MESSAGE_MAP()

	private:

		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	public:

		virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	};

} // Simple2dCharting

#endif // !CHARTCWNDCTRL_H__S2DCHARTING__INCLUDED_
