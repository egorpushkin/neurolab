#include "StdAfx.h"
#include "../../../AreasBuilder.h"

#include "AreaPane.h"

AreaPane::AreaPane(Workspace::IAreasProject* piAreasProject, uint areaIndex)
	: contentDialog_(piAreasProject, areaIndex)
{
}

AreaPane::~AreaPane(void)
{
}

BEGIN_MESSAGE_MAP(AreaPane, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int AreaPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	contentDialog_.Create(AreaPaneContentDlg::IDD, this);
	contentDialog_.ShowWindow(SW_SHOW);

	return 0;
}

void AreaPane::StyleDispl(DWORD dwDsp)
{
	m_StyleDisplay = dwDsp;

	CGuiControlBar::StyleDispl(dwDsp);
}

