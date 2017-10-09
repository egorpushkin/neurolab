#pragma once

#include "..\SolutionUI\NewScriptDlg.h"

class CSolutionOperation_NewScript
{
public:
	static bool NewScript(
		CScriptEnvMainDlg* pDialog, 
		bool RemoveExistingFile = true)
	{
		if (!pDialog->mSolutionObj.IsCreated())
		{
			AfxMessageBox("The solution has not been created yet.");
			return false;
		}
		
		CNewScriptDlg mDlg;
		mDlg.bNewScript = RemoveExistingFile;
		int res = mDlg.DoModal();
		if (res != IDOK)
			return false;
        		
		CSolutionItem* pItem = 
			pDialog->mSolutionObj.AddItem(mDlg.mFileName, CString(_T("")), 
				RemoveExistingFile);
		pDialog->AddItem(pItem);
		pDialog->bIsChanged = true;

		return true;
	}
};