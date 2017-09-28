// PluginBar.cpp : implementation file
//

#include "stdafx.h"
#include "DemoPlugin.h"
#include "PluginBar.h"

#include "interface_idds.h"
#include ".\pluginbar.h"
// CPluginBar dialog

IMPLEMENT_DYNAMIC(CPluginBar, CDialog)
CPluginBar::CPluginBar(CWnd* pParent /*=NULL*/)
	: CDialog(CPluginBar::IDD, pParent)
{
	bIsBarCreated = false;
}

CPluginBar::~CPluginBar()
{
}

void CPluginBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPluginBar, CDialog)
END_MESSAGE_MAP()

// IPluginBarControl implementations section
bool CPluginBar::IsBarCreated()
{
	return bIsBarCreated;
}

void CPluginBar::SetBarState(bool bState)
{
	bIsBarCreated = bState;
}

CDialog* CPluginBar::GetBarDialog()
{
	return (CDialog*)this;
}

int CPluginBar::GetBarIDD()
{
	return IDD;
}

CString CPluginBar::GetBarTitle()
{
	return _T("Demo Plugin Bar");
}

// IObject implementations section
CString	CPluginBar::GetClassString()
{
	return _T("CPluginBar");
}

void CPluginBar::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IPluginBarControl:
		*ppvObject = (IPluginBarControl*)this;
		break;	
	}
}

// CPluginBar message handlers


void CPluginBar::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//__super::OnOK();
}

void CPluginBar::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//__super::OnCancel();
}
