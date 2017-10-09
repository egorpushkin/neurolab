#pragma once


// BandPaneContentDlg dialog

class BandPaneContentDlg : public CDialog
{
	DECLARE_DYNAMIC(BandPaneContentDlg)

public:
	BandPaneContentDlg(Workspace::IAreasProject* piAreasProject, Workspace::Band* pBand, CWnd* pParent = NULL);   // standard constructor
	virtual ~BandPaneContentDlg();

	// Dialog Data
	enum { IDD = IDD_BAND_DISPL_DLG };

	virtual BOOL				Create(UINT resourceId, CWnd* pParentWnd = NULL);

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void				OnOK();
	virtual void				OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void				OnSize(UINT nType, int cx, int cy);

	CDisplayPGMCtrl				bandDisplayCtrl_;

private:
	Workspace::IAreasProject*	piAreasProject_;
	Workspace::Band*			pBand_;
};
