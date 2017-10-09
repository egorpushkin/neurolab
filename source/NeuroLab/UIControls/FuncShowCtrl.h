#pragma once


// CFuncShowCtrl
#include "CmnFunction.h"

class CFuncShowCtrl : public CWnd
{
	DECLARE_DYNAMIC(CFuncShowCtrl)

public:
	CFuncShowCtrl();
	virtual ~CFuncShowCtrl();

	sFunction*	FunctionParam;

	bool		bIsDragging;
	CPoint		PrevDragPosition;

	int			iGrigRange;
	void		SetScale(int Range)
	{
		iGrigRange = Range;
	}

	PPROCESS_FUNCTION_ROUTINE	pfnFunction;
	void	SetFunction(PPROCESS_FUNCTION_ROUTINE	Function)
	{
		pfnFunction = Function;
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
};


