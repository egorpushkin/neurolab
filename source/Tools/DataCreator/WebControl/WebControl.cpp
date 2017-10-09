#include "StdAfx.h"
#include ".\webcontrol.h"

#include "Mshtml.h"

#include "../resource.h"

#define OLE_CTRL_ID_RANGE_FIRST		1000
#define OLE_CTRL_ID_RANGE_LAST		50000

IMPLEMENT_DYNAMIC(CWebControl, CWebBrowser)
CWebControl::CWebControl(void)
{
	pDocHostUIHandlerImpl = new CDocHostUIHandler();
}

CWebControl::~CWebControl(void)
{
	delete pDocHostUIHandlerImpl;

	ReleaseStates();
}

void CWebControl::ReleaseStates()
{
	while (mWebStates.GetCount() > 0)
	{
		CWebControlState* pState = mWebStates.GetHead();
		mWebStates.RemoveHead();

        delete pState;
	}
}

BEGIN_MESSAGE_MAP(CWebControl, CWebBrowser)	
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CWebControl, CWebBrowser)
	ON_EVENT_RANGE(CWebControl,	OLE_CTRL_ID_RANGE_FIRST, OLE_CTRL_ID_RANGE_LAST,
		259, DocumentComplete, 
		VTS_I4 VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT_RANGE(CWebControl, OLE_CTRL_ID_RANGE_FIRST, OLE_CTRL_ID_RANGE_LAST, 
		250, BeforeNavigate2, 
		VTS_I4 VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()

BOOL CWebControl::DocumentComplete(UINT CtlID, LPDISPATCH pDisp, VARIANT* URL)
{
	USES_CONVERSION;    
	
	csCurrentURL = W2T((LPCWSTR)URL->pbVal);

	CWebControlState* pFoundState = FindStateByURL(csCurrentURL);
	if (pFoundState)
		pDocHostUIHandlerImpl->SetGetPropertyCallback(pFoundState->GetGetPropertyCallback(), 
			pFoundState->GetCallbackData());

	CustomizeWebBrowser();
	UpdateStateHandlers();

	return TRUE;
}

BOOL CWebControl::BeforeNavigate2(UINT CtlID, LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{	
	USES_CONVERSION; 

	csCurrentURL = W2T((LPCWSTR)URL->pbVal);

	CWebControlState* pFoundState = FindStateByURL(csCurrentURL);
	if (pFoundState)
		pDocHostUIHandlerImpl->SetGetPropertyCallback(pFoundState->GetGetPropertyCallback(), 
			pFoundState->GetCallbackData());

	return TRUE;
}

void CWebControl::CustomizeWebBrowser()
{
	IUnknown* pUnknown = GetControlUnknown();
	if (!pUnknown)
		return;

	IWebBrowser2 *pBrowser = NULL;
	HRESULT hr = pUnknown->QueryInterface(IID_IWebBrowser2, (void**)&pBrowser);
	if (!SUCCEEDED(hr))	
	{
		pUnknown->Release();

		return;
	}

	IDispatch* pDocumentDispatch = NULL;
	pBrowser->get_Document(&pDocumentDispatch);
	if (!pDocumentDispatch)
	{
		pUnknown->Release();
		pBrowser->Release();

		return;
	}

	IHTMLDocument2* pHTMLDocument = NULL;
	hr = pDocumentDispatch->QueryInterface(IID_IHTMLDocument2,(void**)&pHTMLDocument);
	if (!SUCCEEDED(hr))
	{
		pUnknown->Release();
		pBrowser->Release();
		pDocumentDispatch->Release();

		return;
	}

	ICustomDoc* pCustomDoc = NULL;
	hr = pHTMLDocument->QueryInterface(IID_ICustomDoc, (void**)&pCustomDoc);
	if (!SUCCEEDED(hr))
	{
		pUnknown->Release();
		pBrowser->Release();
		pDocumentDispatch->Release();
		pHTMLDocument->Release();

		return;
	}

	pCustomDoc->SetUIHandler(pDocHostUIHandlerImpl);

	pUnknown->Release();
	pBrowser->Release();
	pDocumentDispatch->Release();
	pHTMLDocument->Release();
	pCustomDoc->Release();
}

void CWebControl::FreeCustomizationData()
{
}

void CWebControl::UpdateStateHandlers()
{
	CWebControlState* pFoundState = FindStateByURL(csCurrentURL);

	if (!pFoundState)
		return;

	IUnknown* pUnknown = GetControlUnknown();
	if (!pUnknown)
		return;

	IWebBrowser2 *pBrowser = NULL;
	HRESULT hr = pUnknown->QueryInterface(IID_IWebBrowser2, (void**)&pBrowser);
	if (!SUCCEEDED(hr))
	{
		pUnknown->Release();

		return;
	}

	IDispatch* pDocumentDispatch = NULL;
	pBrowser->get_Document(&pDocumentDispatch);
	if (!pDocumentDispatch)
	{
		pUnknown->Release();
		pBrowser->Release();

		return;
	}

	IHTMLDocument2* pHTMLDocument = NULL;
	hr = pDocumentDispatch->QueryInterface(IID_IHTMLDocument2,(void**)&pHTMLDocument);
	if (!SUCCEEDED(hr))
	{
		pUnknown->Release();
		pBrowser->Release();		
		pDocumentDispatch->Release();

		return;
	}

	IHTMLElementCollection* pElementCollection = NULL;
	pHTMLDocument->get_all(&pElementCollection);
	if (!SUCCEEDED(hr))
	{
		pUnknown->Release();
		pBrowser->Release();		
		pDocumentDispatch->Release();
		pHTMLDocument->Release();

		return;
	}

	USES_CONVERSION;

	long iElementLength;
	pElementCollection->get_length(&iElementLength);
	for (long i=0;i<iElementLength;i++)
	{
		IDispatch* pElementDispatch = NULL;
		pElementCollection->item(COleVariant(i), COleVariant(i), &pElementDispatch);
		if (!pElementDispatch)
			continue;

		IHTMLElement* pHTMLElement = NULL;
		hr = pElementDispatch->QueryInterface(IID_IHTMLElement,(void**)&pHTMLElement);
		if (!SUCCEEDED(hr))
		{
			pElementDispatch->Release();

			continue;
		}

		CString csAtributeName = "name";
		BSTR bstrAttribName = csAtributeName.AllocSysString();
		COleVariant varT;
		pHTMLElement->getAttribute(bstrAttribName, 0, &varT);
		BSTR bstrValue = varT.bstrVal;

		CString csValue = W2T(bstrValue);

		pFoundState->CreateEnumerator();
		while (CInvokeShell* pShell = pFoundState->GetNextInvokeShell())
			if (pShell->GetName() == csValue)
			{
				VARIANT varT;
				varT.vt = VT_DISPATCH;
				varT.pdispVal = pShell;
				HRESULT res = pHTMLElement->put_onclick(varT);

				break;
			}

		pElementDispatch->Release();
		pHTMLElement->Release();
	}

	//pUnknown->Release();
	//pBrowser->Release();		
	//pDocumentDispatch->Release();
	//pHTMLDocument->Release();
	//pElementCollection->Release();	
}

CWebControlState* CWebControl::AddState(CString& csName, CString& csFile)
{
	CWebControlState* pState = new CWebControlState(csName, csFile);
	mWebStates.AddTail(pState);

	return pState;
}

void CWebControl::ShowState(CString& csName)
{
	for(POSITION pos = mWebStates.GetHeadPosition();pos;)
	{
		CWebControlState* pState = mWebStates.GetNext(pos);
		if (pState->GetStateName() == csName)
		{
			USES_CONVERSION;

			VARIANT varURL;
			varURL.vt = VT_BSTR;
			varURL.pbVal = (BYTE*)T2W(pState->GetFileName().GetBuffer());

			Navigate2(&varURL, NULL, NULL, NULL, NULL);			

			return;
		}
	}
}

void CWebControl::Refresh()
{
	CWebBrowser::Refresh();

	UpdateStateHandlers();
}

void CWebControl::UpdateState()
{
	USES_CONVERSION;

	VARIANT varURL;
	varURL.vt = VT_BSTR;
	varURL.pbVal = (BYTE*)T2W(csCurrentURL.GetBuffer());

	Navigate2(&varURL, NULL, NULL, NULL, NULL);
}

CWebControlState* CWebControl::FindStateByURL(CString& URL)
{
	CString tmURL(URL);
	tmURL.MakeUpper();

	for(POSITION pos = mWebStates.GetHeadPosition();pos;)
	{
		CWebControlState* pState = mWebStates.GetNext(pos);
		CString csStateName = pState->GetStateName();
		csStateName.MakeUpper();

		if (tmURL.Find(csStateName) != -1)
			return pState;
	}

	return NULL;
}