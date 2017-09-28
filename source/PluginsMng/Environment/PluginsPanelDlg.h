#pragma once

#include "..\Resource.h"
// CPluginsPanelDlg dialog

#include "PluginsPanelCore.h"
#include "..\Manager\ContainerCore.h"

#include "..\UIControls\InfoBar.h"
#include "..\StandartControls\ATreeCtrl.h"
#include "afxcmn.h"

class CPluginsPanelDlg : public CDialog, public IPluginsPanelControl
{
	DECLARE_DYNAMIC(CPluginsPanelDlg)

public:
	CPluginsPanelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPluginsPanelDlg();

// Dialog Data
	enum { IDD = IDD_PLUGINS_PANEL };

	CInfoBar			mPanelInfoBar;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// IPluginsPanel declarations section
public:
	virtual BOOL			CreatePanelDlg(CWnd * pWnd);	
	virtual BOOL			ShowPanel(int iCmdShow);
	virtual void			MovePanel(int iX, int iY, int iWidth, int iHeight);
	virtual void			GetPanelRect(CRect* pRect);

	virtual void			SetAppController(IAppController* pController);

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void ** ppvObject);

	virtual BOOL OnInitDialog();

	void					EnablePluginControls(BOOL bEnable);
	
	CTreeCtrl				mPluginsTree;
	
	HTREEITEM				htiRoot;
	HTREEITEM				htiPluginsRoot;
	HTREEITEM				htiWrongsRoot;

	void					SetAppFolder(CString& csFolder);
	void					SetPluginsContainer(IPluginsContainer* pContainer);

	void					CreatePluginsTreeHeader();
	void					ShowPluginsTree();
	void					CleanPluginsTree();

	void					ShowPluginBar(CPluginInstance* pInstance);

private:
	IAppController*			pAppController;
	IPluginsContainer*		pPluginsContainer;
	CString					csAppFolder;

	int iPropWndsCount;

public:
	afx_msg void OnBnClickedStartPlugin();
	afx_msg void OnBnClickedPluginProperties();
	afx_msg void OnBnClickedRefreshPluginsTree();
	int mPluginsCount;
	afx_msg void OnTvnSelchangedPluginsTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkPluginsTree(NMHDR *pNMHDR, LRESULT *pResult);
};
