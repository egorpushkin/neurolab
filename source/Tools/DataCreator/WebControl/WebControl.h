#pragma once

#include "WebBrowser.h"

#include "WebControlState.h"

#include "DocHostUIHandler.h"

class CWebControl : public CWebBrowser
{
	DECLARE_DYNAMIC(CWebControl)

public:
	CWebControl(void);
	~CWebControl(void);
    
	CWebControlState* AddState(CString& csName, CString& csFile);
	void			ShowState(CString& csName);

	void			UpdateState();

public:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	// Web Browser events
	BOOL			DocumentComplete(UINT CtlID, LPDISPATCH pDisp, VARIANT* URL);
	BOOL			BeforeNavigate2(UINT CtlID, LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);

	// Web Browser redeclarations
	void			Refresh();
private:

	CList<CWebControlState*, CWebControlState*> mWebStates;
	CString			csCurrentURL;

	void			ReleaseStates();
	void			UpdateStateHandlers();

	void			CustomizeWebBrowser();
	void			FreeCustomizationData();

	CWebControlState* FindStateByURL(CString& URL);

	// customization data fields
	CDocHostUIHandler*	pDocHostUIHandlerImpl;

	IDispatch*			pDispatch;
};
