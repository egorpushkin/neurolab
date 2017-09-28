#pragma once

#include "..\ScriptEnvMainDlg.h"

#include "SolutionUI/NewSolutionDlg.h"

#include "SaveSolution.h"

class CSolutionOperation_NewSolution
{
public:
	static bool CreateNewSolution(
		CScriptEnvMainDlg* pDialog)
	{
		if (pDialog->mSolutionObj.IsCreated())
		{
			int res = AfxMessageBox("The solution is already opened.\nAre you sure that you want to close it?", MB_YESNO);
            if (res != IDYES)
				return false;	

			if (pDialog->bIsChanged)
			{
				int res = AfxMessageBox("The solution has been changed.\nDo you want to save changes?", MB_YESNO);
				if (res == IDYES)
					CSolutionOperation_SaveSolution::SaveSolution(pDialog);			
			}

			pDialog->mSolutionObj.DestroySolution();
			pDialog->CloseSolution();
		}

		CNewSolutionDlg mDlg;
		int res = mDlg.DoModal();
		if (res != IDOK)
			return false;

		pDialog->mSolutionObj.CreateSolution(mDlg.mSolutionName, mDlg.mFileName);
		pDialog->ShowEmptySolution();
		pDialog->bIsChanged = false;
	
		return true;
	}
};