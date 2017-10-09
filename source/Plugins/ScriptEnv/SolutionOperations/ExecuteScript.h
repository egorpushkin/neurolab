#pragma once

#include "../SolutionUI/ProcessScriptDlg.h"

class CSolutionOperation_ExecuteScript
{
public:
	static bool ExecuteScript(
		CScriptEnvMainDlg* pDialog)
	{
		if (!pDialog->pCurrentSolutionItem)
            return false;
		
		CProcessScriptDlg mDlg;
		mDlg.csAppFolder = pDialog->csAppFolder;
		mDlg.pSolutionObj = &pDialog->mSolutionObj;
		mDlg.pCurrentSolutionItem = pDialog->pCurrentSolutionItem;
		mDlg.pAppController = pDialog->pAppController;
		mDlg.pImportManagerComponent = &pDialog->mImportManager;
		mDlg.DoModal();	

		return true;
	}
};