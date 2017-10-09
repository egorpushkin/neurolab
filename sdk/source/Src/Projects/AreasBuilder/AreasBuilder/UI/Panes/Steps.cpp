#include "StdAfx.h"
#include "../../AreasBuilder.h"

#include "Steps.h"

CSteps::CSteps(void)
{
}

CSteps::~CSteps(void)
{
}

BEGIN_MESSAGE_MAP(CSteps, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CSteps::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	stepsDlg_.Create(CStepsDlg::IDD, this);
	stepsDlg_.ShowWindow(SW_SHOW);

	return 0;
}

void CSteps::StyleDispl(DWORD dwDsp)
{
	m_StyleDisplay = dwDsp;

	CGuiControlBar::StyleDispl(dwDsp);
}

