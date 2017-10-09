#pragma once

class CSolutionOperation_OpenSolution
{
public:
	static bool OpenSolution(
		CScriptEnvMainDlg* pDialog,
		bool fromRepository = false)
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

		CFileDialog	mFileDlg(
			TRUE, "", "", 
			OFN_OVERWRITEPROMPT, 
			"Neuro Laboratory Scripts Solution v1.0|*.nlssln||");

		INT_PTR res = mFileDlg.DoModal();
		if (res != IDOK)
			return false;
		
		pDialog->mSolutionObj.CreateSolution(CString(_T("")), mFileDlg.GetPathName(), false);
		pDialog->mSolutionObj.LoadSolution();

		pDialog->ShowEmptySolution();

		// Displaying Script Items
		pDialog->mSolutionObj.CreateEnumerator();
		while (CSolutionItem* pItem = pDialog->mSolutionObj.GetNextItem())
			pDialog->AddItem(pItem);

		// Displaying Data Items
		pDialog->mSolutionObj.CreateDataEnumerator();
		while (CDataFileItem* pItem = pDialog->mSolutionObj.GetNextDataItem())
			pDialog->AddDataItem(pItem);

		// Displaying Bitmap Items
		pDialog->mSolutionObj.CreateBitmapsEnumerator();
		while (CBitmapItem* pItem = pDialog->mSolutionObj.GetNextBitmap())
			pDialog->AddBitmapItem(pItem);

		// Displaying Project Items
		pDialog->mSolutionObj.CreateProjectsEnumerator();
		while (CProjectItem* pItem = pDialog->mSolutionObj.GetNextProject())
			pDialog->AddProjectItem(pItem);
		
		pDialog->bIsChanged = false;

		return true;
	}
};
