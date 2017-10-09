#include "StdAfx.h"
#include "../../AreasBuilder.h"
#include "ProjectWorkspace.h"

#include "../Interfaces/IHandler.h"

using namespace ProjectUI;

CProjectWorkspace::CProjectWorkspace(void)
{
}

CProjectWorkspace::~CProjectWorkspace(void)
{
}

BEGIN_MESSAGE_MAP(CProjectWorkspace, CGuiControlBar)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, IDC_PROJECT_TREE, OnNMDblclkProjectTree)
END_MESSAGE_MAP()

int CProjectWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Creating Images List
	mImagesList.Create (IDB_PROJECT_ICONS, 16, 20, RGB (255, 0, 0));

    // Creating tabs container
	if (!mTabProjectExplorer.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this, 0x9999))
		return -1;

	// Creating 'Project Explorer' tab
	CreateProjectExplorerContainer();

	// Configuring tabs container
	mTabProjectExplorer.SetImageList(IDB_PROJECT_ICONS, 16,21, RGB (255, 0, 0));

	// Adding 'Project Explorer' tab
	mTabProjectExplorer.Addtab(&mContProjectExplorer, _T("Project Explorer"), 0);

	return 0;
}

int CProjectWorkspace::CreateProjectExplorerContainer()
{
	if (!mContProjectExplorer.Create(WS_CHILD | WS_VISIBLE, 
		CRect(0,0,0,0), &mTabProjectExplorer, 124))
		return -1;

/*	mContProjectExplorer.AddComponen(&mToolProjectExplorer);

	mToolProjectExplorer.AlingButtons(CGuiMiniTool::ALIGN_LEFT);
	mToolProjectExplorer.SetImageList(IDB_PROJECT_ICONS, 16,22, RGB (255, 0, 0));
	mToolProjectExplorer.AutoSize(FALSE);
	mToolProjectExplorer.AddButton(24, ID_REFRESH, NULL, _T(""), _T("Open Project"));*/

	// Creating and configuring 'Project Explorer' tab content control
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
		TVS_LINESATROOT | TVS_HASBUTTONS ;
	if (!mTreeProjectExplorer.Create(dwStyle, CRect(0,0,0,0), &mContProjectExplorer, IDC_PROJECT_TREE))
		return -1;
	mTreeProjectExplorer.SetImageList(&mImagesList,TVSIL_NORMAL);

	mContProjectExplorer.AddComponen(&mTreeProjectExplorer);

	return 0;
}

void CProjectWorkspace::StyleDispl(DWORD dwDsp)
{
	m_StyleDisplay=dwDsp;

	//mToolProjectExplorer.StyleDispl(dwDsp);
	mTabProjectExplorer.StyleDispl(dwDsp);

	CGuiControlBar::StyleDispl(dwDsp);
}

void CProjectWorkspace::OnNMDblclkProjectTree(NMHDR* /* pNMHDR */, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiSelected = mTreeProjectExplorer.GetSelectedItem();
	if (htiSelected)
	{
		IHandler* piHandler = (IHandler*)mTreeProjectExplorer.GetItemData(htiSelected);
		if (piHandler)
		{
			piHandler->Invoke();		
		}
	}

	*pResult = 0;
}
