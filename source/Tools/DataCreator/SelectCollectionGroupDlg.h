#pragma once


// CSelectCollectionGroupDlg dialog

#include "CmnDataCollection.h"
#include "afxcmn.h"

#define SCG_MODE_VIEW		0x0001
#define SCG_MODE_SELEECT	0x0002

class CSelectCollectionGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectCollectionGroupDlg)

public:
	CSelectCollectionGroupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectCollectionGroupDlg();

// Dialog Data
	enum { IDD = IDD_SELECT_COLLECTION_GROUP_DLG };

	void					SetDataCollection(IDataCollection* pCollection);
	void					SetCtrlMode(int Mode);

	void					ShowSubgroups(CCollectionGroup* pGroup, HTREEITEM htiParent);
	void					ShowGroupInformation(CCollectionGroup* pGroup);

	int						iCtrlMode;

	IDataCollection*		pDataCollection;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedCollectionGroupsTree(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl mGroupsTree;
	CString mGroupName;
	int mDataItems;
	int mSubgroups;
};
