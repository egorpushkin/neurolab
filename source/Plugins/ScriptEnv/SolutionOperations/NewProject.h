#pragma once

class CSolutionOperation_NewProject
{
public:
	static bool NewProject(
		CScriptEnvMainDlg* pDialog)
	{
		if (!pDialog->mSolutionObj.IsCreated())
		{
			AfxMessageBox("The solution has not been created yet.");
			return false;
		}

		CFileDialog	mFileDlg(true, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Project File v1.0|*.nlproj||");
		INT_PTR res = mFileDlg.DoModal();
		if (res != IDOK)
			return false;
				
		CProjectItem* pItem = 
			pDialog->mSolutionObj.AddProjectFile(mFileDlg.GetPathName());
		pDialog->AddProjectItem(pItem);
		pDialog->bIsChanged = true;

		return true;
	}
};