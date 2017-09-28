#pragma once


// AreaPaneContentDlg dialog

class AreaPaneContentDlg : public CDialog
{
	DECLARE_DYNAMIC(AreaPaneContentDlg)

public:
	AreaPaneContentDlg(Workspace::IAreasProject* piAreasProject, uint areaIndex, CWnd* pParent = NULL);   // standard constructor
	virtual ~AreaPaneContentDlg();

// Dialog Data
	enum { IDD = IDD_AREA_DISPL_DLG };

	virtual BOOL				Create(UINT resourceId, CWnd* pParentWnd = NULL);

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void				OnOK();
	virtual void				OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void				OnSize(UINT nType, int cx, int cy);

	CDataImageCtrl				areaMapCtrl_;

private:
	Workspace::IAreasProject*	piAreasProject_;
	uint						areaIndex_;
};
