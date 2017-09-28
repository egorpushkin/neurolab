// ATreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ATreeCtrl.h"
#include ".\atreectrl.h"

#include "..\\Resource.h"
// CATreeCtrl

IMPLEMENT_DYNAMIC(CATreeCtrl, CTreeCtrl)
CATreeCtrl::CATreeCtrl()
{
	bDragging = false;
	mDragAcceptWnd = NULL;

	OnSelChange = NULL;
}

CATreeCtrl::~CATreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CATreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, OnNMClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

HTREEITEM	CATreeCtrl::InsertActiveItem(CString Title, ItemDataStruct * iData, HTREEITEM ParentItem)
{
	if (!iData)
		iData = new ItemDataStruct;
	iData->htiThis = InsertItem(
		TVIF_IMAGE|TVIF_PARAM|TVIF_SELECTEDIMAGE|TVIF_STATE|TVIF_TEXT,
		Title,
		iData->FreeImage,
		iData->SltdImage,
		iData->State,
		iData->State,
		(LPARAM)iData,
		ParentItem,
		iData->htiPrevItem);
	return iData->htiThis;
}


// CATreeCtrl message handlers


void CATreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	SetSelection();
	IEventProcess(lClk)
	*pResult = 0;
}

void CATreeCtrl::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	SetSelection();
	IEventProcess(rClk);
	*pResult = 0;
}

void CATreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	IEventProcess(Select);

	if (OnSelChange)
		(*OnSelChange)((DWORD)this);

	*pResult = 0;
}

CPoint CATreeCtrl::SetSelection(CPoint * mPoint)
{
	CPoint LocPoint;
	UINT nFlags; 
	if (!mPoint)
	{
		GetCursorPos(&LocPoint);
		ScreenToClient(&LocPoint);
	} else
		LocPoint = *mPoint; 
	HTREEITEM htiSltd = HitTest(LocPoint, &nFlags);
	if (htiSltd)
		Select(htiSltd, TVGN_CARET);
	return LocPoint;
}

BOOL CATreeCtrl::DeleteAllItems(void)
{
	BOOL result = CTreeCtrl::DeleteAllItems();
	
	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	rect.InflateRect(1, 1, 1, 1);
	MoveWindow(rect);
	rect.InflateRect(-1, -1, -1, -1);
	MoveWindow(rect);

	return result;
}

void CATreeCtrl::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	HTREEITEM htiSltd = GetSelectedItem();					
	if (htiSltd)											
	{														
		ItemDataStruct * idsItem;							
		idsItem = (ItemDataStruct *)GetItemData(htiSltd);	
		if (idsItem && idsItem->IsDraggingEnabled)	
		{
			bDragging = TRUE;
			SetCapture();
		}
	}

	*pResult = 0;
}

void CATreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bDragging)
	{
		CPoint ptAction;
		GetCursorPos(&ptAction);
		CWnd* wndUnderMouse = WindowFromPoint(ptAction);
		if (wndUnderMouse == mDragAcceptWnd)
		{
			HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_POINTER_COPY);
			HCURSOR hOldCur = SetCursor(hCur);
			DeleteObject(hOldCur);
		}else
		{
			HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_NODROP);
			HCURSOR hOldCur = SetCursor(hCur);
			DeleteObject(hOldCur);
		}
		//AfxGetMainWnd()->ScreenToClient(&ptAction);
		//ImageListDrag->DragMove(ptAction);
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CATreeCtrl::SetDragAcceptWnd(CWnd * pWnd)
{
	mDragAcceptWnd = pWnd;
}

void CATreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bDragging)
	{	
		bDragging = false;
		ReleaseCapture();
		IEventProcess(Dragged);
	}

	CTreeCtrl::OnLButtonUp(nFlags, point);
}

BOOL CATreeCtrl::DeleteItem(HTREEITEM thiToRemove)
{
	BOOL bRet = CTreeCtrl::DeleteItem(thiToRemove);
	
	IEventProcess(Select);

	if (OnSelChange)
		(*OnSelChange)((DWORD)this);

	return bRet;
}


