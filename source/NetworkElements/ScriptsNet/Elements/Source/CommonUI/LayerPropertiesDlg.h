#pragma once

#include "..\..\..\Resource.h"
#include "afxcmn.h"
// CLayerPropertiesDlg dialog

#include "..\..\..\Resource.h"

#include "CmnElement.h"

class CLayerPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CLayerPropertiesDlg)

public:
	CLayerPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLayerPropertiesDlg();

	void			SetElement(IElement* Element);

private:
	IElement*		pElement;

// Dialog Data
	enum { IDD = IDD_LAYER_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mLayerID;
	int mInputsCount;
	int mLayerDimension;
	virtual BOOL OnInitDialog();
	CListCtrl mWeightsCtrl;
protected:
	virtual void OnOK();
};
