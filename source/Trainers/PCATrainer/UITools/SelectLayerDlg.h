#pragma once

#include "../Resource.h"
#include "afxcmn.h"
// CSelectLayerDlg dialog

#include "CmnFactory.h"
#include "CmnLog.h"

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

class CSelectLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectLayerDlg)

public:
	CSelectLayerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectLayerDlg();

// Dialog Data
	enum { IDD = IDD_SELECT_LAYERS_DLG };

	// [Input]
	IElementsCollection*	pElementsCollection;
	ILogProvider*			pLogProvider;
	
	// [Output]
	ILayerControl*			pLayerControl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mLayersList;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
