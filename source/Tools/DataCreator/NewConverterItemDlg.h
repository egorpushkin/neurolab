#pragma once


// CNewConverterItemDlg dialog

#include "CmnDataFile.h"
#include "CmnDataCollection.h"

class CNewConverterItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewConverterItemDlg)

public:
	CNewConverterItemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewConverterItemDlg();

// Dialog Data
	enum { IDD = IDD_NEW_CONVERTER_ITEM_DLG };

	void					SetDataFile(IDataFile* pFile);
	void					SetDataCollection(IDataCollection* pCollection);

	IDataFile*				pDataFile;
	IDataCollection*		pDataCollection;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mGroupName;
	int mSymbolIndex;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedSelectGroupName();
	afx_msg void OnBnClickedSelectSymbolIndex();
};
