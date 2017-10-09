#pragma once


// CInfoBar

#define BT_STANDART_BUTTON			0x0001
#define BT_SEPARATOR				0x0002
#define BT_DROPDOWN_MENU_BUTTON		0x0003

struct sCtrlButton
{
	sCtrlButton()
		: iButtonType(BT_STANDART_BUTTON)
	{
	}

	sCtrlButton(CString& Text, int CtrlID = -1, int Type = BT_STANDART_BUTTON)
		: csText(Text)
		, iCtrlID(CtrlID)
		, iButtonType(Type)
	{ 	
	}

	CString			csText;
	int				iCtrlID;
	int				iButtonType;
};

class CInfoBar : public CWnd
{
	DECLARE_DYNAMIC(CInfoBar)

public:
	CInfoBar();
	virtual ~CInfoBar();

	//				Media Data 
	void			SetMediaDirectory(CString& Directory);
	CString			csMediaDirectory;

	//				Common attributes
	int				iUnderCursorSubCtrlID;

	//				Dragging
	bool			bIsDragging;
	CPoint			pntPrevDrag;
	bool			bIsDraggingEnabled;
	void			SetDragParameters(CRect& rect);
	CRect			DraggingRect;
	bool			IsOverDragPanel(CPoint& point);

	//				Right panel
	bool			bIsOverRightPanel;
	bool			IsOverRightPanel(CPoint& point);
	CMenu			mBarPopupMenu;
	int				iSubMenu;
	bool			bIsMenuInitialized;
	void			SetBarPopupMenu(int MenuResourceID, int SubMenuID);
	void			SetRightPanelTips(CString& text, int iToolID, int iTTMaxWidth = 760);
	bool			bPopupToolAdded;
	bool			bPopupToolTipEnabled;
	CToolTipCtrl	mPopupToolTip;
	int				iRightToolCtrlID;

	CString			csAppFolder;

	//				Tooltips
	CToolTipCtrl	mToolTip;
	bool			bToolTipEnabled;
	bool			bToolAdded;
	int				iToolCtrlID;
	void			SetToolTipText(CString& text, int iToolID, CString& title=CString(""));
	bool			IsOverToolTip(CPoint& point);
	void			InitToolTips(int iTTMaxWidth = 768);

	void			UpdateToolTips();

	//				Control Buttons Functions
	CList<sCtrlButton*, sCtrlButton*>	mButtonsList;
	sCtrlButton*	AddButton(CString& text, int CtrlID = -1, int Type = BT_STANDART_BUTTON);
	void			ReleaseButtons();

	void			ShowButtons(Graphics* pGraphics);
	void			ShowButton(Graphics* pGraphics, sCtrlButton* pButton, int Offset);

	int				CalculateStartButtonsOffset();
	int				CalculateButtonLength(sCtrlButton* pButton);
	int				GetSubControlID(CPoint& point);
	int				GetButtonOffset(sCtrlButton* pButton);

	sCtrlButton*	GetButtonUnderMouse(CPoint& point);

	sCtrlButton*	pActiveButton;

	RectF			GetTestMetrics(CString& Text, CString& FontName, int FontSize, FontStyle Style, Unit MetricsUnit);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
};


