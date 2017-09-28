#pragma once

class CSolutionOperation_CloseSolution
{
public:
	static bool CloseSolution(
		CScriptEnvMainDlg* pDialog)
	{
		if (!pDialog->mSolutionObj.IsCreated())
			return true;

		//int res = AfxMessageBox("The solution is already opened.\nAre you sure that you want to close it?", MB_YESNO);
        //if (res != IDYES)
		//	return false;	

		if (pDialog->bIsChanged)
		{
			int res = AfxMessageBox("The solution has been changed.\nDo you want to save changes?", MB_YESNOCANCEL);
			if (res == IDYES)
				CSolutionOperation_SaveSolution::SaveSolution(pDialog);			
			else if (res == IDCANCEL)
				return false;
		}

		pDialog->mSolutionObj.DestroySolution();
		pDialog->CloseSolution();

		return true;
	}
};