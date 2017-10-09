#pragma once

#include "CmnDecl.h"
#include "System\Directory.h"

#include "..\SolutionUI\ProcessScriptDlg.h"

#include "..\LuaNeuroApi\GlobalStorage.h"

DWORD ExecuteScriptThread(void* param);

class CSolutionOperation_ExecuteScript
{
public:
	static bool ExecuteScript(
		CProcessScriptDlg* pDialog)
	{	
		ILogProvider* pLogProvider = NULL;
		pDialog->QueryInterface(IDD_ILogProvider, (void**)&pLogProvider);
		if (!pLogProvider)
			return false;

		// Initializing global variabls which values are binded to Lua scripts
		CLuaStorage_GlobalEnvironment::csScriptDirectory =
			CPath::GetFileFolder(pDialog->pCurrentSolutionItem->GetFileName());
		CLuaStorage_GlobalEnvironment::csSolutionDirectory = 
			CPath::GetFileFolder(pDialog->pSolutionObj->GetFileName());
		CLuaStorage_GlobalEnvironment::csCurrentDirectory =
			CLuaStorage_GlobalEnvironment::csScriptDirectory;
		CLuaStorage_GlobalEnvironment::csAppDirectory = 
			pDialog->csAppFolder;

		CLuaStorage_LogProvider::iCurPercentage = 0;
		CLuaStorage_LogProvider::pLogProvider = pLogProvider;

		CLuaStorage_Solution::pSolution = pDialog->pSolutionObj;
		CLuaStorage_Solution::pImportManagerComponent = pDialog->pImportManagerComponent;
		CLuaStorage_Solution::FillFilesList();

		pDialog->pAppController->QueryInterface(IDD_INetworkProcessor, 
			(void**)&CLuaStorage_NetworkProcessor::pNetworkProcessor);
		pDialog->pAppController->QueryInterface(IDD_IElementsCollection, 
			(void**)&CLuaStorage_NetworkProcessor::pElementsCollection);

		DWORD_PTR dwThreadPriority = pDialog->GetSelectedPriorityLevel();

		unsigned dwThreadID;
		hThread = __beginthreadex(NULL, 0, ExecuteScriptThread, pDialog, 
			CREATE_SUSPENDED, &dwThreadID);

		SetThreadPriority(hThread, (int)dwThreadPriority);
		ResumeThread(hThread);

		return true;
	}

	static bool TerminateScript(
		CProcessScriptDlg* pDialog)
	{
		if (CSolutionOperation_ExecuteScript::hThread)
		{
			TerminateThread(CSolutionOperation_ExecuteScript::hThread, 0);
			
			CSolutionOperation_ExecuteScript::hThread = NULL;			
		}

		// Destroing temporary data
		CLuaStorage_Solution::ReleaseFilesList();		
		CLuaStorage_FactoriesContainer::ReleaseContainer();

		return true;
	}

	static HANDLE hThread;
};