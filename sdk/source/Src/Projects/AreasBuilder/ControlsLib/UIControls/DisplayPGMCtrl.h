#ifndef DISPLAYPGMCTRL_H__CONTROLSLIB__INCLUDED_
#define DISPLAYPGMCTRL_H__CONTROLSLIB__INCLUDED_

class CDisplayPGMCtrl : public CWnd
{
	DECLARE_DYNAMIC(CDisplayPGMCtrl)

public:
	CDisplayPGMCtrl();
	virtual ~CDisplayPGMCtrl();
	
	void					SetBitmap(IPGMBitmap* piSourceBitmap);

private:
	IPGMBitmap*				piSourceBitmap_;
	Gdiplus::Bitmap*		deviceBitmap_;

	bool					PrepareBitmapContext();

public:
	virtual BOOL			Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void			OnPaint();
	afx_msg BOOL			OnEraseBkgnd(CDC* pDC);	
	afx_msg void			OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !DISPLAYPGMCTRL_H__CONTROLSLIB__INCLUDED_
