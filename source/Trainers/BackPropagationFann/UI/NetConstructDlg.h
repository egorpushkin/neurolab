#pragma once

#include "afxwin.h"
#include "../res/resource.h"

// CNetConstructDlg dialog

class CNetConstructDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetConstructDlg)

public:

	CNetConstructDlg(
		IElementsCollection* piElementsCollection,
		GenericNetwork* pGenericNetwork); 
	virtual ~CNetConstructDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:

	// Private interface
	void InitialDisplayNetworks();
	void FillList(CListBox& listControl, GenericNetwork::NetworkContainer& network);
	void TransferSelectedItem(CListBox& from, CListBox& to);
	void DumpNetwork();
	CString GetElementDim(int index);

private:

	// Dialog Data
	enum { IDD = IDD_NET_CONSTR_TOOL_DLG };

	CListBox sourceList_;
	CListBox targetList_;
	CEdit netDescr_;

	afx_msg void OnBnClickedAddSingle();
	afx_msg void OnBnClickedRemoveSingle();
	afx_msg void OnBnClickedMoveUp();
	afx_msg void OnBnClickedMoveDown();
	afx_msg void OnLbnDblclkSourceList();
	afx_msg void OnLbnDblclkTargetList();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	IElementsCollection* piElementsCollection_;
	GenericNetwork* pGenericNetwork_; 

};
