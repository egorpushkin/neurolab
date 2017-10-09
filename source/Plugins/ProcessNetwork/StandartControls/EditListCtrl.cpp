// EditListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EditListCtrl.h"
#include "InPlaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...)
{
	LV_ITEM item;
    item.iItem = m_List->GetItemCount();
    item.iImage = icon;
	item.lParam = data;
   
    item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

	va_list params;
	va_start(params, num);
	char * temp = va_arg(params,char *);

	item.iSubItem = 0;
    item.pszText = temp;
    m_List->InsertItem(&item);

	for(int i = 1;i<num;i++)
	{
		temp = va_arg(params,char *);
		item.mask = LVIF_TEXT;
		item.iSubItem = i;
		item.pszText = temp;
		m_List->SetItem(&item);
	}
} 

CEditListCtrl::CEditListCtrl()
{
	mpfnVerifyFunc = NULL;
}

CEditListCtrl::~CEditListCtrl()
{
}


BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CEditListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl message handlers

void CEditListCtrl::EditItem( int Item,int SubItem)
{
	CInPlaceEdit	*edit;
	edit = new CInPlaceEdit(Item,SubItem,GetItemText(Item,SubItem));
	
	CHeaderCtrl *jHead=GetHeaderCtrl();
	ASSERT(jHead!=NULL);

	CRect jRect;
	jHead->GetItemRect(SubItem,&jRect);
	CRect Rect;
	GetItemRect(Item,&Rect,LVIR_LABEL);

	Rect.left = jRect.left;
	Rect.right = jRect.right;
		
	edit->Create( WS_BORDER | WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL, Rect,this,1230);
}



void CEditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	LVHITTESTINFO lvhti;	
	lvhti.pt = point;
	SubItemHitTest( &lvhti);

	CHeaderCtrl *mHead=GetHeaderCtrl();
	
	if (mpfnVerifyFunc)
	{
		if ((*mpfnVerifyFunc)(lvhti.iItem, lvhti.iSubItem))
			EditItem(lvhti.iItem,lvhti.iSubItem);
	}
	
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

void CEditListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here

	LV_ITEM	*plvItem = &pDispInfo->item;

	if (plvItem->pszText != NULL)
	{
		SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
	}
	
	/*((CEditListCtrl *)plvItem->lParam)->DestroyWindow();
	delete (CInPlaceEdit *)plvItem->lParam;*/

	
	*pResult = 0;
}
