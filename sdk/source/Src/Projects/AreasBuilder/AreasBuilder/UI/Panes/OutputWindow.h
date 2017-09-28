#pragma once

//////////////////////////////////////////////////////////////////////////
// COutputList Declaration
//////////////////////////////////////////////////////////////////////////	

class COutputList : public CListBox
{
// Construction
public:
	COutputList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputList)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// COutputWindow Declaration
//////////////////////////////////////////////////////////////////////////	

#include "../Interfaces/ILogOutputManager.h"

class COutputWindow 
	: public CGuiControlBar  
	, public ProjectUI::ILogOutputManager
{
	friend class CMainFrame;

	struct LogProvider
	{
		LogProvider(uint tabId, CListBox* pListBox)
			: tabId_(tabId)
			, pListBox_(pListBox)
		{
		}

		uint					tabId_;
		CListBox*				pListBox_;
	};

public:
	COutputWindow();
	virtual ~COutputWindow();

	// Public UI tools
	//////////////////////////////////////////////////////////////////////////  
    virtual void StyleDispl(DWORD dwDsp = GUISTYLE_2003);

	// ILogOutputManager declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual result				DisplayLogMessage(const String& providerName, const String& message, bool performSwitchToProvider = true);
	virtual result				ClearLog(const String& providerName, bool performSwitchToProvider = true);
	virtual result				SwitchToProvider(const String& providerName);

	// ICommon declarations section
	////////////////////////////////////////////////////////////////////////// 
	virtual	ulong				AddRef();
	virtual	ulong				Release();

	virtual String				GetClassString() const;
	virtual result				QueryInterface(REFIID rIID, void** ppObject);

protected:
	ulong						numRef_;

	CGuiWorkTab					workTab_;

	COutputList					projectEventsList_;
	COutputList					pocessingEventsList_;

	map<String, LogProvider>					logProviders_;
	typedef pair<String, LogProvider>			ProviderPair;
	typedef map<String, LogProvider>::iterator	ProvidersIterator;		

protected:
	// COutputWindow message handlers
	//////////////////////////////////////////////////////////////////////////
	//{{AFX_MSG(CMyBar)
	afx_msg int					OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
