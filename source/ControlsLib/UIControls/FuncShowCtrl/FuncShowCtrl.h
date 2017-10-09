#pragma once


// CFuncShowCtrl
#include "CmnDataFactory.h"

class DLL_FUNC_DECLARE CFuncShowCtrl : public CWnd
{
	DECLARE_DYNAMIC(CFuncShowCtrl)

public:
	CFuncShowCtrl();
	virtual ~CFuncShowCtrl();

	IDataFactory*	pDataFactory;

	bool			bIsDragging;
	CPoint			PrevDragPosition;

	int				iGrigRange;
	void			SetScale(int Range)
	{
		iGrigRange = Range;
		Invalidate();
	}

	PPROCESS_FUNCTION_ROUTINE	pfnFunction;
	void			SetCtrlData(IDataFactory* pData)
	{
		pDataFactory = pData;
	}

	int	iXOffset;
	int iYOffset;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
	int				iCurrentIndex;
	float			fCurrentValue;

	void			UpdateCurrentValues(CPoint& point);
};


