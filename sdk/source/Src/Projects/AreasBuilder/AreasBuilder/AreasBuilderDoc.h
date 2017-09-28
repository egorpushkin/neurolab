#pragma once

// Include serialization mechanizm
//////////////////////////////////////////////////////////////////////////
#include "Serialization/XMLProjectParser.h"

class CAreasBuilderDoc : public CDocument
{
protected: // create from serialization only
	CAreasBuilderDoc();
	DECLARE_DYNCREATE(CAreasBuilderDoc)

// Attributes
public:
	Workspace::IAreasProject*	piAreasProject_;

	XMLProjectParser			projectParser_;
    
// Operations
public:
	result						DoOpenProject(const StringA& fileName);
	void						DoCloseProject();

	bool						IsOpened();

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CAreasBuilderDoc();
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
};


