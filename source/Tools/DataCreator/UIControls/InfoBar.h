#pragma once


// CInfoBar

struct sCtrlButton
{
	CString			csText;
	int				iCtrlID;
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
	void			SetDragParameters(CRect * rect);
	CRect			DraggingRect;
	bool			IsOverDragPanel(CPoint & point);

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
	void			AddButton(CString& text, int CtrlID);

	

	int				GetSubControlID(CPoint& point);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


