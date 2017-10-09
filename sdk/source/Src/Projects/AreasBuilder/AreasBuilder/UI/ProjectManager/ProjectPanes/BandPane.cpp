#include "StdAfx.h"
#include "../../../AreasBuilder.h"

#include "BandPane.h"

BandPane::BandPane(Workspace::IAreasProject* piAreasProject, Workspace::Band* pBand)
	: contentDialog_(piAreasProject, pBand)
{
}

BandPane::~BandPane(void)
{
}

BEGIN_MESSAGE_MAP(BandPane, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int BandPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	contentDialog_.Create(BandPaneContentDlg::IDD, this);
	contentDialog_.ShowWindow(SW_SHOW);

	return 0;
}

void BandPane::StyleDispl(DWORD dwDsp)
{
	m_StyleDisplay = dwDsp;

	CGuiControlBar::StyleDispl(dwDsp);
}

