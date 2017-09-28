#if !defined(AFX_EDITLISTCTRL_H__41E80791_9F6B_453F_8E3A_947B0B2119B7__INCLUDED_)
#define AFX_EDITLISTCTRL_H__41E80791_9F6B_453F_8E3A_947B0B2119B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl window

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

typedef bool(*pfnVerifyIsToEdit)(int iItem, int iSubItem);

class CEditListCtrl : public CListCtrl
{
// Construction
public:
	CEditListCtrl();

// Attributes
public:
	pfnVerifyIsToEdit	mpfnVerifyFunc;
	void	SetVerifyingFunc(pfnVerifyIsToEdit	mpfnFunc)
	{
		mpfnVerifyFunc = mpfnFunc;
	}


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditListCtrl();
	void EditItem( int Item,int SubItem);

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditListCtrl)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTCTRL_H__41E80791_9F6B_453F_8E3A_947B0B2119B7__INCLUDED_)
