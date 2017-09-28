#pragma once

typedef CString (*PGETPROPERTY_CALLBACK_ROUTINE)(CString& PropertyName, DWORD Param);

class CExternalDispatchProxy : public IDispatch
{
public:
	CExternalDispatchProxy(PGETPROPERTY_CALLBACK_ROUTINE pfnRoutine, DWORD dwData);
	~CExternalDispatchProxy();

	// IUnknown declarations section
	STDMETHODIMP_(DWORD)AddRef();
	STDMETHODIMP_(DWORD)Release();
	STDMETHODIMP QueryInterface(REFIID riid, void** ppv);

	// IDispatch declarations section
    STDMETHODIMP	GetTypeInfoCount( UINT *pctinfo);
    STDMETHODIMP	GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    STDMETHODIMP	GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames,
						LCID lcid, DISPID *rgDispId);
    STDMETHODIMP	Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
						DISPPARAMS *pDispParams, VARIANT *pVarResult,
						EXCEPINFO  *pExcepInfo, UINT *puArgErr); 
private:
	HRESULT			GetPropertyValue(VARIANTARG& varPropertyName, VARIANT* pVarResult);
	
	ULONG			iRefsCount;

	PGETPROPERTY_CALLBACK_ROUTINE	pfnGetPropertyCallBack;
	DWORD							dwCallbackData;
};
