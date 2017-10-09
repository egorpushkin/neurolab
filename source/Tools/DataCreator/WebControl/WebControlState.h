#pragma once

#include "Templates\Enumerator.h"

#include "InvokeShell.h"
#include "ExternalDispatchProxy.h"

class CWebControlState
{
public:
	CWebControlState() : 
		csStateName(_T(""))
		, csFileName(_T(""))
		, pfnGetPropertyCallBack(NULL)
	{}

	CWebControlState(CString& csName, CString& csFile)
	{
		SetStateName(csName);
		SetFileName(csFile);

		pfnGetPropertyCallBack = NULL;
	}
	
	~CWebControlState()
	{
		DestroyShells();	
	}

	void				SetStateName(CString& csName)
	{
		csStateName = csName;
	}

	void				SetFileName(CString& csFile)
	{
		csFileName = csFile;
	}

	CString				GetStateName()
	{
		return csStateName;
	}

	CString				GetFileName()
	{
		return csFileName;
	}

	void				AddInvokeShell(CString& csName, PEVENT_CALLBACK_ROUTINE pfnFunc, DWORD dwData)
	{
		CInvokeShell* pShell = new CInvokeShell(csName, pfnFunc, dwData);
		mInvokeShells.AddTail(pShell);
	}

	void				SetGetPropertyCallback(PGETPROPERTY_CALLBACK_ROUTINE pfnRoutine, DWORD dwData)
	{
		pfnGetPropertyCallBack = pfnRoutine;
		dwCallbackData = dwData;
	}

	PGETPROPERTY_CALLBACK_ROUTINE GetGetPropertyCallback()
	{
		return pfnGetPropertyCallBack;
	}

	DWORD				GetCallbackData()
	{
		return dwCallbackData;
	}

	ENUMERATOR(mInvokeShells, CInvokeShell*, CreateEnumerator, GetNextInvokeShell, posShells)

private:
	void				DestroyShells()
	{
		while (mInvokeShells.GetCount())
		{
			CInvokeShell* pShell = mInvokeShells.GetHead();
			mInvokeShells.RemoveHead();
	
			delete pShell;
		}	
	}

private:
	CString				csStateName;
	CString				csFileName;

	CList<CInvokeShell*, CInvokeShell*>	mInvokeShells;

	PGETPROPERTY_CALLBACK_ROUTINE	pfnGetPropertyCallBack;
	DWORD							dwCallbackData;
};


