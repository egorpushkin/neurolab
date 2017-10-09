#pragma once

class CProjectWorkspace 
	: public CGuiControlBar
{
	friend class CMainFrame;

protected:
	CGuiTabWnd			mTabProjectExplorer;
	CTreeCtrl			mTreeProjectExplorer;

	CImageList			mImagesList;
	
	CGuiContainer		mContProjectExplorer;
	CGuiMiniTool		mToolProjectExplorer;

public:
	CProjectWorkspace(void);
	virtual ~CProjectWorkspace(void);

	virtual void		StyleDispl(DWORD dwDsp = GUISTYLE_2003);
	int					CreateProjectExplorerContainer();

	DECLARE_MESSAGE_MAP()

	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnNMDblclkProjectTree(NMHDR *pNMHDR, LRESULT *pResult);
};
