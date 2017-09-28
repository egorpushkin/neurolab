#pragma once

#include "AreaPaneContentDlg.h"

class AreaPane
	: public CGuiControlBar
{
protected:
	AreaPaneContentDlg	contentDialog_;

public:
	AreaPane(Workspace::IAreasProject* piAreasProject, uint areaIndex);
	virtual ~AreaPane(void);

	virtual void		StyleDispl(DWORD dwDsp = GUISTYLE_2003);

	DECLARE_MESSAGE_MAP()

private:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);

};
