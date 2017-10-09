#pragma once

class DLL_FUNC_DECLARE ChartPanelCtrl : public CWnd
{
public:
	ChartPanelCtrl();
	virtual ~ChartPanelCtrl();

	// Public interface
	//////////////////////////////////////////////////////////////////////////


private:
	// Data members
	//////////////////////////////////////////////////////////////////////////


protected:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void			OnPaint();
};
