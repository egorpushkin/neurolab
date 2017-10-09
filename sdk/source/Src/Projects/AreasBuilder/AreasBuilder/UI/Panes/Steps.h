#pragma once

#include "../Dialogs/StepsDlg.h"

class CSteps
	: public CGuiControlBar
{
protected:
	CStepsDlg			stepsDlg_;

public:
	CSteps(void);
	virtual ~CSteps(void);

	virtual void		StyleDispl(DWORD dwDsp = GUISTYLE_2003);

	DECLARE_MESSAGE_MAP()

private:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);

};
