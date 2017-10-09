#pragma once

#include "BandPaneContentDlg.h"

class BandPane
	: public CGuiControlBar
{
protected:
	BandPaneContentDlg	contentDialog_;

public:
	BandPane(Workspace::IAreasProject* piAreasProject, Workspace::Band* pBand);
	virtual ~BandPane(void);

	virtual void		StyleDispl(DWORD dwDsp = GUISTYLE_2003);

	DECLARE_MESSAGE_MAP()

private:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);

};
