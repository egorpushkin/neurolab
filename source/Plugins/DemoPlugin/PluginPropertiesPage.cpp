// PluginPropertiesPage.cpp : implementation file
//

#include "stdafx.h"
#include "DemoPlugin.h"
#include "PluginPropertiesPage.h"

#include "interface_idds.h"
// CPluginPropertiesPage dialog

IMPLEMENT_DYNAMIC(CPluginPropertiesPage, CDialog)
CPluginPropertiesPage::CPluginPropertiesPage(CWnd* pParent /*=NULL*/)
	: CDialog(CPluginPropertiesPage::IDD, pParent)
{
}

CPluginPropertiesPage::~CPluginPropertiesPage()
{
}

void CPluginPropertiesPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPluginPropertiesPage, CDialog)
END_MESSAGE_MAP()

// IPluginPropertiesControl implementations section
CDialog* CPluginPropertiesPage::GetPropertyDialog()
{
	return (CDialog*)this;
}

int CPluginPropertiesPage::GetDialogIDD()
{
	return IDD;
}

CString CPluginPropertiesPage::GetPropertyPageTitle()
{
	return _T("Demo plugin properties");
}

void CPluginPropertiesPage::ProcessUpdateProperties()
{

}

// IObject implementations section
CString	CPluginPropertiesPage::GetClassString()
{
	return _T("CPluginPropertiesPage");
}

void CPluginPropertiesPage::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IPluginPropertiesControl:
		*ppvObject = (IPluginPropertiesControl*)this;
		break;	
	}
}

// CPluginPropertiesPage message handlers
