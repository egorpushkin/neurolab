#pragma once

typedef void(*TreeReactionFunc)(void * Param);

struct	ItemDataStruct
{
	ItemDataStruct()
	{
		lClk = rClk = Select = Dragged = NULL;
		ItemData = NULL;

		FreeImage = SltdImage = NULL;
		htiPrevItem = TVI_LAST;
		htiThis = NULL;

		State = NULL;

		IsDraggingEnabled = false;
		dwStructIdent = 0xff01ff01;
	}
	DWORD				dwStructIdent;
	
	TreeReactionFunc	lClk;
	TreeReactionFunc	rClk;
	TreeReactionFunc	Select;
	TreeReactionFunc	Dragged;

	void	*	ItemData;
	int		State;

	int		FreeImage;
	int		SltdImage;

	bool	IsDraggingEnabled;

	HTREEITEM	htiPrevItem;
	HTREEITEM	htiThis;
};

#define	IParDef(DefItem, DefData, Param, DataType)			\
	ItemDataStruct * DefItem = (ItemDataStruct*)Param;		\
	DataType * DefData = (DataType *)DefItem->ItemData;		\

#define	IEventProcess(EventFunction)						\
	HTREEITEM htiSltd = GetSelectedItem();					\
	if (htiSltd)											\
	{														\
		ItemDataStruct * idsItem;							\
		idsItem = (ItemDataStruct *)GetItemData(htiSltd);	\
		if (idsItem)										\
			if (idsItem->dwStructIdent == 0xff01ff01)		\
				if (idsItem->EventFunction)					\
					(*idsItem->EventFunction)(idsItem);		\
	}														\

// CATreeCtrl

class CATreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CATreeCtrl)

public:

	TreeReactionFunc	OnSelChange;

	CATreeCtrl();
	virtual ~CATreeCtrl();

	bool	bDragging;
	CWnd*	mDragAcceptWnd;

	HTREEITEM	InsertActiveItem(CString Title, ItemDataStruct * iData = NULL, HTREEITEM ParentItem = TVI_ROOT);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg virtual void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	CPoint SetSelection(CPoint * mPoint = NULL);
	BOOL DeleteAllItems(void);
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void SetDragAcceptWnd(CWnd * pWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	BOOL DeleteItem(HTREEITEM thiToRemove);
};


