#include "stdafx.h"

#include "ChartPanelCtrl.h"
#include ".\chartpanelctrl.h"

ChartPanelCtrl::ChartPanelCtrl()
{

}

ChartPanelCtrl::~ChartPanelCtrl()
{

}

BEGIN_MESSAGE_MAP(ChartPanelCtrl, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void ChartPanelCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}
