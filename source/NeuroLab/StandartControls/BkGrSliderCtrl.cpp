// BkGrSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "..\NeuroLab.h"
#include "BkGrSliderCtrl.h"
#include ".\bkgrsliderctrl.h"


// CBkGrSliderCtrl

IMPLEMENT_DYNAMIC(CBkGrSliderCtrl, CSliderCtrl)
CBkGrSliderCtrl::CBkGrSliderCtrl()
{
}

CBkGrSliderCtrl::~CBkGrSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CBkGrSliderCtrl, CSliderCtrl)
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
END_MESSAGE_MAP()



// CBkGrSliderCtrl message handlers


BOOL CBkGrSliderCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	/*CRect rect;
	GetClientRect(&rect);

	CBrush mBrush(RGB(255, 255, 255));
	pDC->FillRect(&rect, &mBrush);
	
	mBrush.DeleteObject();*/

	return FALSE;

	//return CSliderCtrl::OnEraseBkgnd(pDC);
}
void CBkGrSliderCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)pNMHDR;
	CDC *pDC = CDC::FromHandle(lpcd->hdc);
	switch(lpcd->dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW ;
			break;
			//return;  
		case CDDS_ITEMPREPAINT:
		if (lpcd->dwItemSpec == TBCD_THUMB)
		{
			*pResult = CDRF_DODEFAULT;
			break;
		}
		if (lpcd->dwItemSpec == TBCD_CHANNEL)
		{
			CRect crect;
			GetClientRect(crect);

			CBrush mBrush(RGB(255, 255, 225));
			pDC->FillRect(&crect, &mBrush);
			mBrush.DeleteObject();

			*pResult = 0;
			break;
		}
	}
}
