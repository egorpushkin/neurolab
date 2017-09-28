#pragma once

class CSolutionOperation_RemoveItem
{
public:
	static bool RemoveItem(
		CScriptEnvMainDlg* pDialog)
	{
		HTREEITEM htiCurrent = pDialog->mSolutionTree.GetSelectedItem();
		if (!htiCurrent)
			return false;

		IObject* pObject = (IObject*)pDialog->mSolutionTree.GetItemData(htiCurrent);
		if (!pObject)
			return false;

		if (pObject->GetClassString() == CString(_T("CSolutionItem")))
		{
			CSolutionItem* pItem = (CSolutionItem*)pObject;       		

			CString tmMessage = CString(_T("Are you sure that you want to remove the following script from the solution?\n")) + 
				CString(_T("Script name: ")) + CString(CPath::GetFileName(pItem->GetFileName())) + CString(_T("."));
			
			int res = AfxMessageBox(tmMessage, MB_YESNO);
			if (res != IDYES)
				return false;

			// Removing script file from the environment
			pDialog->RemoveScriptFile(htiCurrent, pItem);

			// Removing script file from the solution
			pDialog->mSolutionObj.RemoveSolutionItem(pItem);

			pDialog->bIsChanged = true;

		} else if (pObject->GetClassString() == CString(_T("CDataFileItem")))
		{
			CDataFileItem* pItem = (CDataFileItem*)pObject;

			CString tmMessage = CString(_T("Are you sure that you want to remove the following data item from the solution?\n")) + 
				CString(_T("Data file name: ")) + CString(CPath::GetFileName(pItem->GetFileName())) + CString(_T("."));
			
			int res = AfxMessageBox(tmMessage, MB_YESNO);
			if (res != IDYES)
				return false;

			// Removing data file from the environment
			pDialog->RemoveDataFile(htiCurrent, pItem);

			// Removing data item from the solution
			pDialog->mSolutionObj.RemoveDataItem(pItem);

			pDialog->bIsChanged = true;
		} else if (pObject->GetClassString() == CString(_T("CBitmapItem")))
		{
			CBitmapItem* pItem = (CBitmapItem*)pObject;

			CString tmMessage = CString(_T("Are you sure that you want to remove the following bitmap from the solution?\n")) + 
				CString(_T("Bitmap file name: ")) + CString(CPath::GetFileName(pItem->GetFileName())) + CString(_T("."));
			
			int res = AfxMessageBox(tmMessage, MB_YESNO);
			if (res != IDYES)
				return false;

			// Removing bitmap file from the environment
			pDialog->RemoveBitmap(htiCurrent, pItem);

			// Removing bitmap file from the solution
			pDialog->mSolutionObj.RemoveBitmap(pItem);		

			pDialog->bIsChanged = true;
		} else if (pObject->GetClassString() == CString(_T("CProjectItem")))
		{
			CProjectItem* pItem = (CProjectItem*)pObject;

			CString tmMessage = CString(_T("Are you sure that you want to remove the following project from the solution?\n")) + 
				CString(_T("Project file name: ")) + CString(CPath::GetFileName(pItem->GetFileName())) + CString(_T("."));
			
			int res = AfxMessageBox(tmMessage, MB_YESNO);
			if (res != IDYES)
				return false;

			// Removing project file from the environment
			pDialog->RemoveProject(htiCurrent, pItem);

			// Removing project file from the solution
			pDialog->mSolutionObj.RemoveProject(pItem);		

			pDialog->bIsChanged = true;
		}

		return true;
	}
};