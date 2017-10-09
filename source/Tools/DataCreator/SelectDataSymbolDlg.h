#pragma once


// CSelectDataSymbolDlg dialog

#include "CmnDataFile.h"

#define SDS_MODE_VIEW		0x0001
#define SDS_MODE_SELEECT	0x0002

class CSelectDataSymbolDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDataSymbolDlg)

public:
	CSelectDataSymbolDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectDataSymbolDlg();

// Dialog Data
	enum { IDD = IDD_SELECT_DATA_SYMBOL_DLG };

	CDataImageCtrl			mSymbolCtrl;

	void					SetDataFile(IDataFile* pFile, bool bInputs);
	void					SetCtrlMode(int Mode);

	int						iCtrlMode;

    IDataFile*				pDataFile;
	bool					bShowInputs;

	int						GetDataLength();
	int						GetSymbolsCount();
	IDataFactory*			GetSymbol(int Symbol);
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	int mOutputsCount;
	int mSymbolDimension;
	int mSymbolIndex;
	afx_msg void OnBnClickedUpSymbol();
	afx_msg void OnBnClickedDownSymbol();
	afx_msg void OnBnClickedSymbolProperties();
};
