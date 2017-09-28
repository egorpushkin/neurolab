#pragma once

#include "CmnObjects.h"
#include "CmnApp.h"

interface IPluginsPanelControl : public IObject
{
	virtual BOOL			CreatePanelDlg(CWnd * pWnd) = 0;
	virtual BOOL			ShowPanel(int iCmdShow) = 0;
	virtual void			MovePanel(int iX, int iY, int iWidth, int iHeight) = 0;
	virtual void			GetPanelRect(CRect* pRect) = 0;

	virtual void			SetAppController(IAppController* pController) = 0;
};