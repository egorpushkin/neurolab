#pragma once


// CExportCollectionDlg dialog

#include "CmnLog.h"
#include "afxwin.h"

#include "CmnConverter.h"

class CExportCollectionDlg : 
	public CDialog, 
	public ILogProvider
{
	DECLARE_DYNAMIC(CExportCollectionDlg)

public:
	CExportCollectionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExportCollectionDlg();

// Dialog Data
	enum { IDD = IDD_EXPORTING_COLLECTION_DLG };

	void			SetCollectionConverter(CCollectionConverter* Converter);
	CCollectionConverter*	mConverter;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedConvert();
	CString mFileName;
	int mDimension;

public:
// ILogProvider declarations section
	virtual void			ClearLog();
	virtual void			AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

	CListBox mLog;
};
