#include "stdafx.h"
#include "ExternalDispatchProxy.h"

// The DISPID constants
#define DISPID_GETPROPERTYVALUE			0x000001

CExternalDispatchProxy::CExternalDispatchProxy(PGETPROPERTY_CALLBACK_ROUTINE pfnRoutine, DWORD dwData)
	: iRefsCount(0)
	, pfnGetPropertyCallBack(pfnRoutine)
	, dwCallbackData(dwData)
{
}

CExternalDispatchProxy::~CExternalDispatchProxy()
{
}

STDMETHODIMP_(DWORD) CExternalDispatchProxy::AddRef()
{
	return ++iRefsCount;
}

STDMETHODIMP_(DWORD) CExternalDispatchProxy::Release()
{
	--iRefsCount;
	if(iRefsCount == 0)
	{
		delete this;
		return 0;
	}
	return iRefsCount;
}

STDMETHODIMP CExternalDispatchProxy::QueryInterface(REFIID riid, void** ppv)
{
	if(riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if(riid == IID_IDispatch)
		*ppv = (IDispatch*)this;
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	((IUnknown*)(*ppv))->AddRef();
	return S_OK;
}

// IDispatch implementations section
STDMETHODIMP CExternalDispatchProxy::GetTypeInfoCount( UINT *pctinfo)
{
	*pctinfo = 0;
	return S_OK;
}

STDMETHODIMP CExternalDispatchProxy::GetTypeInfo( 
    UINT iTInfo,
    LCID lcid,
    ITypeInfo **ppTInfo)
{
	*ppTInfo = NULL;
	return E_NOTIMPL;
}

STDMETHODIMP CExternalDispatchProxy::GetIDsOfNames( 
    REFIID riid,
    LPOLESTR *rgszNames,
    UINT cNames,
    LCID lcid,
    DISPID *rgDispId)
{
	if(cNames > 1) 
		return E_INVALIDARG;

	if(_wcsicmp(*rgszNames, L"GetPropertyValue") == 0)
	{
		*rgDispId = DISPID_GETPROPERTYVALUE;
		return S_OK;
	} else
		return DISP_E_UNKNOWNNAME;
}

STDMETHODIMP CExternalDispatchProxy::Invoke( 
    DISPID dispIdMember,
    REFIID riid,
    LCID lcid,
    WORD wFlags,
    DISPPARAMS *pDispParams,
    VARIANT *pVarResult,
    EXCEPINFO  *pExcepInfo,
    UINT *puArgErr)
{
	switch(dispIdMember)
	{
	case DISPID_GETPROPERTYVALUE: 
		return GetPropertyValue(pDispParams->rgvarg[0], pVarResult);
	default:
		return DISP_E_UNKNOWNINTERFACE;
	}
}

HRESULT CExternalDispatchProxy::GetPropertyValue(VARIANTARG& varPropertyName, VARIANT* pVarResult)
{
	USES_CONVERSION;

	if (pfnGetPropertyCallBack)
	{
		CString csPropertyValue = (*pfnGetPropertyCallBack)(
			CString(W2T(varPropertyName.bstrVal)), dwCallbackData);
		
		pVarResult->vt = VT_BSTR;
		pVarResult->bstrVal	= csPropertyValue.AllocSysString();

		return S_OK;
	}

	CString csPropertyValue(_T(""));
	pVarResult->vt = VT_BSTR;
	pVarResult->bstrVal	= csPropertyValue.AllocSysString();

	return S_OK;
}