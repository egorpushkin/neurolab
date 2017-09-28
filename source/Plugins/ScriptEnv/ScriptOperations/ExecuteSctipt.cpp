#include "StdAfx.h"
#include "ExecuteScript.h"

#include "..\Common\CmnLua.h"

HANDLE CSolutionOperation_ExecuteScript::hThread = NULL;

DWORD ExecuteScriptThread(void* param)
{
	DWORD dwRet = 0;

	CProcessScriptDlg* pDialog = (CProcessScriptDlg*)param;
	
	CCmnLua tmLuaEnvironment(pDialog->pCurrentSolutionItem->GetFileName());
	bool bRet = tmLuaEnvironment.ExecuteScript();
	if (bRet)
		pDialog->AddLogMessage(CString(_T("N")), 
			CString(_T("Script has been executed successfully.")), 
			CString(_T("Scripting Environment")));

	// Destroing temporary data
	CLuaStorage_Solution::ReleaseFilesList();		
	
	CLuaStorage_FactoriesContainer::ReleaseContainer();
	CLuaStorage_DataFilesContainer::ReleaseContainer();
	CLuaStorage_BitmapsContainer::ReleaseContainer();
	CLuaStorage_ChartsContainer::ReleaseContainer();

	CSolutionOperation_ExecuteScript::hThread = NULL;
	pDialog->OnFinishScript();
	
    return dwRet;
}
