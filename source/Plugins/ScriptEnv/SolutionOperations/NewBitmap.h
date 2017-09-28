#pragma once

class CSolutionOperation_NewBitmap
{
public:
	static bool NewBitmap(
		CScriptEnvMainDlg* pDialog)
	{
		if (!pDialog->mSolutionObj.IsCreated())
		{
			AfxMessageBox("The solution has not been created yet.");
			return false;
		}

		CFileDialog	mFileDlg(true, "", "", OFN_OVERWRITEPROMPT, "PGM Bitmap File|*.pgm||");
		INT_PTR res = mFileDlg.DoModal();
		if (res != IDOK)
			return false;
				
		CBitmapItem* pItem = 
			pDialog->mSolutionObj.AddBitmapFile(mFileDlg.GetPathName());
		pDialog->AddBitmapItem(pItem);
		pDialog->bIsChanged = true;

		return true;
	}
};