#if !defined(AFX_BCGPINTELLISENSEWND_H__2D884D5A_B4C1_4EE0_A5D6_3D8703CA99D1__INCLUDED_)
#define AFX_BCGPINTELLISENSEWND_H__2D884D5A_B4C1_4EE0_A5D6_3D8703CA99D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPIntelliSenseWnd.h : header file
//
#include "BCGCBPro.h"
#include "BCGPIntelliSenseLB.h"

class CBCGPEditCtrl;

/////////////////////////////////////////////////////////////////////////////
// CBCGPIntelliSenseWnd frame

class BCGCBPRODLLEXPORT CBCGPIntelliSenseWnd : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CBCGPIntelliSenseWnd)
public:
	CBCGPIntelliSenseWnd();           // protected constructor used by dynamic creation

	virtual BOOL Create (CObList& lstData, DWORD dwStyle, CPoint pt, 
						 CWnd* pParentWnd, CFont* pLBFont, CImageList* pImageList = NULL, 
						 CRuntimeClass* pLBDataRTC = NULL);
// Attributes
public:
	CBCGPEditCtrl* GetParentEditCtrl () {return m_pParentEditCtrl;}
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPIntelliSenseWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBCGPIntelliSenseWnd();

	// Generated message map functions
	//{{AFX_MSG(CBCGPIntelliSenseWnd)
	afx_msg void OnDestroy();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT DeleteItem (WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	CBCGPBaseIntelliSenseLB*	m_pLstBoxData;
	CFont						m_lbFont;
	CBCGPEditCtrl*				m_pParentEditCtrl;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPINTELLISENSEWND_H__2D884D5A_B4C1_4EE0_A5D6_3D8703CA99D1__INCLUDED_)
