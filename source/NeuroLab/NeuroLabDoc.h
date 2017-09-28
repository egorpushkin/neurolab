// NeuroLabDoc.h : interface of the CNeuroLabDoc class
//


#pragma once

#include "NeuroObjects\NeuroFactory.h"

class CNeuroLabDoc : public CDocument
{
protected: // create from serialization only
	CNeuroLabDoc();
	DECLARE_DYNCREATE(CNeuroLabDoc)

// Attributes
public:
	CNeuroFactory	mFactory;

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CNeuroLabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
};


