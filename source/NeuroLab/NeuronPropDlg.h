#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CNeuronPropDlg dialog
#include "StandartControls\ATreeCtrl.h"

#include "CmnElement.h"
#include "CmnOutput.h"

// Event notification functions
void OnSelChangeDendrites(void * Param);
void OnSelChangeDendritesAddit(void * Param);

void OnSelChangeAxons(void * Param);
void OnSelChangeAxonsAddit(void * Param);

class CNeuronPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CNeuronPropDlg)

public:
	CNeuronPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNeuronPropDlg();

// Dialog Data
	enum { IDD = IDD_NEURONPROPERTIESDLG };

	// Creation and initialization functions
	virtual BOOL		Create(int iIDD, CWnd* pParentWnd = NULL);
	void				EnableInterface(bool bIsToEnable);

	void				ShowElement(IElement* pNewElement);
	void				ShowDendrites(CConnection* pConnection = NULL);
	void				ShowAxons(CConnection* pConnection = NULL);

    void				SetBuilderControl(IBuilderControl* pControl);

	bool				EnableEditConnectionDimension(CConnection* pConnection);

private:
	IElement*			pActiveElement;

	IBuilderControl*	pBuilderControl;

// Dialog Controls' variables
public:
	CButton				mCtrlRemoveDendr;
	CButton				mUpMoveDendrite;
	CButton				mDownMoveDendrite;
	float				mDendrWeight;
	CEdit				mCtrlDendrWeight;
	CATreeCtrl			mDendrites;
	CEdit				mCtrlDendriteCount;
	int					mDendriteCount;
	
	CButton				mCtrlRemoveAxon;
	CButton				mUpMoveAxon;
	CButton				mDownMoveAxon;
	CATreeCtrl			mAxons;
	CEdit				mCtrlAxonCount;
	int					mAxonCount;

	CEdit				mCtrlFunctionName;
	CButton				mCtrlSelectFunction;

	int					mNeuronID;
	CString				mElTitle;

// Message and command handlers
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void			OnOK();
	virtual void			OnCancel();

public:
	afx_msg void			OnBnClickedRemoveaxon();
	afx_msg void			OnBnClickedSelectfunction();
	afx_msg void			OnBnClickedUpMoveDendrite();
	afx_msg void			OnBnClickedDownMoveDendrite();
	afx_msg void			OnBnClickedUpMoveAxon();
	afx_msg void			OnBnClickedDownMoveAxon();
	afx_msg void			OnBnClickedRemovedendrite();
	afx_msg void			OnEnChangeDendriteweight();
	afx_msg void			OnEnChangeDendriteCount();
	afx_msg void			OnEnChangeAxonCount();
};
