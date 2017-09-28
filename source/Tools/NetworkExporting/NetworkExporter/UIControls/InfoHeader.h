#pragma once

// CInfoHeader

//#include "..\OutputLib\GDIPDevice.h"

typedef void (*pfnCBInfoHeaderOnDraw)(Graphics*, CRect&);

class CInfoHeader : public CWnd
{
	DECLARE_DYNAMIC(CInfoHeader)

public:
	CInfoHeader();
	virtual ~CInfoHeader();

	bool	IsOverLink;

	pfnCBInfoHeaderOnDraw	pfnOnDraw;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetOnDrawHandler(pfnCBInfoHeaderOnDraw);
protected:
	virtual void PreSubclassWindow();
};


