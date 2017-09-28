#pragma once

class CDispatchImpl : public IDispatch
{
	// IDispatch implementations section
	STDMETHODIMP GetTypeInfoCount(UINT FAR* pctinfo)
	{
		if (pctinfo == NULL)
		{
			return E_INVALIDARG;
		}

		*pctinfo = 1;
		return NOERROR;
	}

	STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo)
	{
		if (ppTInfo == NULL)
			return E_INVALIDARG;

		*ppTInfo = NULL;

		if(iTInfo != 0)
			return DISP_E_BADINDEX;

		*ppTInfo = NULL;
		return NOERROR;
	}

	STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames,
		LCID lcid, DISPID FAR* rgDispId)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, 
		WORD wFlags, DISPPARAMS FAR *pDispParams, VARIANT FAR *pVarResult, 
		EXCEPINFO FAR *pExcepInfo, unsigned int FAR *puArgErr)
	{	
		return S_OK;
	}

	// IUnknown implementation section
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject)
	{
		return S_OK;	
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

	int						iRefsCount;
};