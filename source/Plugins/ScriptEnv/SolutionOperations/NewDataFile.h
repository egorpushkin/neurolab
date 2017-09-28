#pragma once

class CSolutionOperation_NewDataFile
{
public:
	static bool NewDataFile(
		CScriptEnvMainDlg* pDialog)
	{
		if (!pDialog->mSolutionObj.IsCreated())
		{
			AfxMessageBox("The solution has not been created yet.");
			return false;
		}

		CFileDialog	mFileDlg(true, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data File v1.0|*.nldfile||");
		INT_PTR res = mFileDlg.DoModal();
		if (res != IDOK)
			return false;
				
		CDataFileItem* pItem = 
			pDialog->mSolutionObj.AddDataFile(mFileDlg.GetPathName());
		pDialog->AddDataItem(pItem);
		pDialog->bIsChanged = true;

		return true;
	}
};