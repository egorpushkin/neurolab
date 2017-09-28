#pragma once


// CDataImageCtrl

#include "CmnDataFactory.h"

class DLL_FUNC_DECLARE CDataImageCtrl : public CWnd
{
	DECLARE_DYNAMIC(CDataImageCtrl)

public:
	CDataImageCtrl();
	virtual ~CDataImageCtrl();

	void			SetCtrlParams(int XDimension, int YDimension, bool EnableEdit);
	void			SetCtrlParams(int XDimension, int YDimension);
	void			SetCtrlData(IDataFactory* pData);
	void			EnableEdit(bool EnableEdit);
	void			SetMarker(float Marker);

	int				GetXDimension();
	int				GetYDimension();

	void			ShowPropertiesDlg();
	void			ShowSelectMarkerDlg();
	void			ShowAdvancedEditorDlg();
	void			ShowSaveAsDlg();

	void			SetToolTipID(int ID);

	float			GetMarkerValue();

private:
	bool			bEnableEdit;
	int				iXDimension;
	int				iYDimension;

	IDataFactory*	pDataFactory;

	float			fMarker;
	int				iMarkerDiameter;

	bool			bPressed;

	void			SetCheck(CPoint& point);
	void			UpdateCurrentValue(CPoint& point);
	void			DisplayMarker(int XIndex, int YIndex);

	// Color range properties
	float			fMinDataValue;
	float			fMaxDataValue;

	bool			bUseRedMask;
	bool			bUseGreenMask;
	bool			bUseBlueMask;

	int				iRedComponent;
	int				iGreenComponent;
	int				iBlueComponent;

/*	int				iToolTipID;
	CToolTipCtrl	mToolTip;
	bool			bToolTipCreated;*/

	float			fCurrentValue;

	bool			bShowGrid;
	bool			bShowInfo;

	int				iScale;
	int				iXOffset;
	int				iYOffset;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


