#pragma once

class CSolutionOperation_SaveSolution
{
public:
	static bool SaveSolution(
		CScriptEnvMainDlg* pDialog)
	{
		if (pDialog->pCurrentSolutionItem)
		{
			CString tmCurrentContent;
			pDialog->mWorkspaceEdit.GetWindowText(tmCurrentContent);

			pDialog->pCurrentSolutionItem->UpdateScriptFileContent(tmCurrentContent);
		}	

		bool bRet = pDialog->mSolutionObj.SaveSolution();
		if (bRet)
		{
			//AfxMessageBox("Solution was successfully saved.");
			pDialog->bIsChanged = false;
		}

		return false;
	}
};