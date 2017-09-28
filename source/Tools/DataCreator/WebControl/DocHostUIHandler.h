#pragma once

#include "mshtmhst.h"

#include "ExternalDispatchProxy.h"

class CDocHostUIHandler
	: public IDocHostUIHandler
{
public:
	CDocHostUIHandler()
	{
		pfnGetPropertyCallBack = NULL;
	}

	~CDocHostUIHandler()
	{
	}

private:
	// IDocHostUIHandler implementation section
	HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO *)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE ShowUI(DWORD,IOleInPlaceActiveObject *,IOleCommandTarget *,IOleInPlaceFrame *,IOleInPlaceUIWindow *)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE HideUI(void)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE UpdateUI(void)
	{
		return S_OK;
	}
	
	HRESULT STDMETHODCALLTYPE EnableModeless(BOOL)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT,IOleInPlaceUIWindow *,BOOL)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE TranslateAcceleratorA(LPMSG,const GUID *,DWORD)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR * ,DWORD)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget *,IDropTarget ** )
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetExternal(IDispatch** ppDispatch)
	{
		CExternalDispatchProxy* pProxyObject = new CExternalDispatchProxy(pfnGetPropertyCallBack, dwCallbackData);
		return pProxyObject->QueryInterface(IID_IDispatch, (void**)ppDispatch);
	}

	HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD,OLECHAR *,OLECHAR ** )
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject *,IDataObject ** )
	{
		return S_OK;
	}

	// IUnknown implementation section
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject)
	{
		*ppvObject = NULL;
		return E_NOTIMPL;	
	}

	ULONG STDMETHODCALLTYPE AddRef(void)
	{
		iRefsCount++;
		return iRefsCount;
	}

	ULONG STDMETHODCALLTYPE Release(void)
	{
		iRefsCount--;
		return iRefsCount;
	}

	int								iRefsCount;

public:
	void SetGetPropertyCallback(PGETPROPERTY_CALLBACK_ROUTINE pfnRoutine, DWORD dwData)
	{
		pfnGetPropertyCallBack = pfnRoutine;
		dwCallbackData = dwData;
	}

private:
	PGETPROPERTY_CALLBACK_ROUTINE	pfnGetPropertyCallBack;
	DWORD							dwCallbackData;
};
