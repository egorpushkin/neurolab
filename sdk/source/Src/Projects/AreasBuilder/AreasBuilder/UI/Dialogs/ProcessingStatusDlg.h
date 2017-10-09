#pragma once

namespace ProjectUI
{
	class ProjectManager;
}

class CProcessingStatusDlg 
	: public CDialog
	, public ProjectUI::IStatusUIProvider
{
	DECLARE_DYNAMIC(CProcessingStatusDlg)

public:
	CProcessingStatusDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessingStatusDlg();

	// IStatusUIProvider declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual void				SetAreasProject(Workspace::IAreasProject* piAreasProject);
	virtual void				SetProjectManager(ProjectUI::ProjectManager* pProjectManager);

	virtual INT_PTR				ShowModalDialog();
	virtual void				CloseModalDialog();
	virtual void				InitialUpdateUI();
	virtual void				AllowCloseDialog();

	virtual void				UpdatePercentage(uint percentage);

	// ICommon declarations section
	////////////////////////////////////////////////////////////////////////// 
	virtual	ulong				AddRef();
	virtual	ulong				Release();

	virtual String				GetClassString() const;
	virtual result				QueryInterface(REFIID rIID, void** ppObject);

private:
	ulong						numRef_;

	bool						allowedToClose_;

	ProjectUI::ProjectManager*	pProjectManager_;
	Workspace::IAreasProject*	piAreasProject_;

protected:
	// Dialog Data
	enum { IDD = IDD_PROCESSING_STATUS };

	DECLARE_MESSAGE_MAP()

	// Dialog members
	//////////////////////////////////////////////////////////////////////////
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();
	virtual void				OnOK();
	virtual void				OnCancel();

	afx_msg void				OnBnClickedEnableVisualization();
	afx_msg void				OnCbnSelchangeClassToDisplay();
	afx_msg void				OnBnClickedTerminateBuilding();

	afx_msg void				OnTimer(UINT nIDEvent);
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void				OnMouseMove(UINT nFlags, CPoint point);

	void						EnableVisualization();
	void						DisplaySelectedArea();

	// Dragging
	bool						dragging_;
	CPoint						prevDragPos_;

	// Controls
	CDataImageCtrl				areaMapCtrl_;
	CProgressCtrl				buildingProgress_;
	CStatic						buildingStatus_;
	CComboBox					areaSelector_;	
	BOOL						enableVisualization_;
};
