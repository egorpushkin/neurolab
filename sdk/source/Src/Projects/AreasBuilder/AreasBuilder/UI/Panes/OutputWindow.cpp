#include "stdafx.h"

#include "OutputWindow.h"
#include "../../Resource.h"

#include "../Common/Providers.h"

using namespace ProjectUI;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// COutputWindow Implementation
//////////////////////////////////////////////////////////////////////////	

COutputWindow::COutputWindow()
	: numRef_(1)
	, workTab_()
	, projectEventsList_()
	, pocessingEventsList_()
	, logProviders_()
{
}

COutputWindow::~COutputWindow()
{
}


BEGIN_MESSAGE_MAP(COutputWindow, CGuiControlBar)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// COutputWindow message handlers
//////////////////////////////////////////////////////////////////////////
int COutputWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!workTab_.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 124))
		return -1;
		
	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	CRect rectClient (0, 0, lpCreateStruct->cx, lpCreateStruct->cy);
	
	const DWORD dwStyle =  LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	projectEventsList_.Create (dwStyle, rectClient, &workTab_, 1);
	pocessingEventsList_.Create (dwStyle, rectClient, &workTab_, 2);
	
	projectEventsList_.SetFont (&m_Font);
	pocessingEventsList_.SetFont (&m_Font);

	projectEventsList_.SetOwner (this);
	pocessingEventsList_.SetOwner (this);
	
	workTab_.Addtab(&projectEventsList_, _T("Project Events"), 0);
	workTab_.Addtab(&pocessingEventsList_, _T("Processing Events"), 1);

	workTab_.SetActualTitle(FALSE);
	SetIcon(IDB_HELP_ICONS,16,4,RGB(255,0,0),2);

	// Initializing log providers
	logProviders_.insert(ProviderPair(PROJECT_LOG, LogProvider(0, &projectEventsList_)));
	logProviders_.insert(ProviderPair(PROCESSING_LOG, LogProvider(1, &pocessingEventsList_)));

	return 0;
}

void COutputWindow::OnSize(UINT nType, int cx, int cy) 
{
	CGuiControlBar::OnSize(nType, cx, cy);

}

// Public UI tools
//////////////////////////////////////////////////////////////////////////  
void COutputWindow::StyleDispl(DWORD dwDsp)
{
	m_StyleDisplay=dwDsp;
	workTab_.StyleDispl(dwDsp);
	CGuiControlBar::StyleDispl(dwDsp);
}

// ILogOutputManager declarations section
//////////////////////////////////////////////////////////////////////////
result COutputWindow::DisplayLogMessage(const String& providerName, const String& message, bool performSwitchToProvider)
{
	ProvidersIterator iter = logProviders_.find(providerName);
	if (logProviders_.end() == iter)
		return S_FALSE;	

	iter->second.pListBox_->AddString(message.c_str());

	int itemsCount = iter->second.pListBox_->GetCount();
	if (itemsCount >= 1)	
		iter->second.pListBox_->SetCurSel(itemsCount - 1);
	
	if (performSwitchToProvider)
		SwitchToProvider(providerName);

	return S_OK;
}

result COutputWindow::ClearLog(const String& providerName, bool performSwitchToProvider)
{
	ProvidersIterator iter = logProviders_.find(providerName);
	if (logProviders_.end() == iter)
		return S_FALSE;	

	iter->second.pListBox_->ResetContent();
    
	if (performSwitchToProvider)
		SwitchToProvider(providerName);

	return S_OK;
}

result COutputWindow::SwitchToProvider(const String& providerName)
{
	ProvidersIterator iter = logProviders_.find(providerName);
	if (logProviders_.end() == iter)
		return S_FALSE;	

	workTab_.SetCurtab(iter->second.tabId_);

	return S_OK;	
}

// ICommon implementations section
ulong COutputWindow::AddRef()
{
	return ++numRef_;						
}

ulong COutputWindow::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String COutputWindow::GetClassString() const
{
	return _T("COutputWindow");
}

result COutputWindow::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = static_cast<ICommon*>(this);
	}
	if (rIID == IID_ILogOutputManager)
	{		
		*ppObject = static_cast<ILogOutputManager*>(this);
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	static_cast<ICommon*>(this)->AddRef();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// COutputList Implementation
//////////////////////////////////////////////////////////////////////////	
COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}


BEGIN_MESSAGE_MAP(COutputList, CListBox)
	//{{AFX_MSG_MAP(COutputList)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void COutputList::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CListBox::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:
	ShowScrollBar(SB_HORZ, FALSE);
	ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);
}

