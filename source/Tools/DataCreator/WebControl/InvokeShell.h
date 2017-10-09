#pragma once

typedef void (*PEVENT_CALLBACK_ROUTINE)(DWORD Param);

class CInvokeShell : public IDispatch
{
public:
	CInvokeShell()
	{
		pfnCallbackRoutine = NULL;
	}

	CInvokeShell(CString& csName, PEVENT_CALLBACK_ROUTINE pfnFunc, DWORD dwData)
	{
		csInvokeName = csName;
		pfnCallbackRoutine = pfnFunc;
		dwRoutineData = dwData;
	}

	CString GetName()
	{
		return csInvokeName;
	}

private:
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
		if (pfnCallbackRoutine)
			(*pfnCallbackRoutine)(dwRoutineData);		

		return S_OK;
	}

	// IUnknown implementations section
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

	CString					csInvokeName;
	PEVENT_CALLBACK_ROUTINE	pfnCallbackRoutine;
	DWORD					dwRoutineData;
};