#pragma once
#include "afxcmn.h"

// Controls
#include "StandartControls/ATreeCtrl.h"
#include "WebControl/WebControl.h"

#include "DataCollection/DataCollection.h"

class CDataCollectionsDlg;
#include "CollectionsMng/SolutionParams.h"

// Global Operations View Handlers
#include "CollectionsMng/Handlers/OperationsView.h"

// Collection View Operation Handlers
#include "CollectionsMng/Handlers/CollectionView.h"

// Group View Operation Handlers
#include "CollectionsMng/Handlers/GroupView.h"

// Solution Control Callback Command Handlers
#include "CollectionsMng/Handlers/SolutionMain.h"

// Solution Control Specific Callback Command Handlers
#include "CollectionsMng/Handlers/SolutionSpecific.h"

// Callback External Handlers
#include "CollectionsMng/Handlers/ExternalProperties.h"

// CDataCollectionsDlg dialog
class CDataCollectionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataCollectionsDlg)

public:
	CDataCollectionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataCollectionsDlg();

// Dialog Data
	enum { IDD = IDD_DATA_COLLECTIONS };

	// Initialization 
	void			GetApplicationFolder();
	void			ShowLogoScreen();
	void			InitializeWebControlStates();
	void			InitializeCollectionSolution();

	// Release
	void			ReleaseControls();

	// Formating output(solution)
	CString			PrepareCollectionName(CString& Name);
	CString			PrepareGroupName(CString& Name);

	// Building solution structure
	void			ShowCollection();
	void			CreateGroup(HTREEITEM htiParent, CCollectionGroup* pGroup);
	void			AddDataItem(HTREEITEM htiParent, CCollectionDataItem* pItem);

	HTREEITEM		htiCollectionRoot;

	// Global information
	CString			csAppFolder;

	// Collection state
	CDataCollection	mDataCollection;

	CCollectionGroup* pCurrentGroup;
	CCollectionDataItem* pCurrentDataItem;

	// Collection independent information
	CString			csFileName;
	bool			bModified;
   
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL Create(int IDD, CWnd* pParentWnd = NULL);	
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	CATreeCtrl mCollectionTree;
	CWebControl mCollectionProperties;
};
