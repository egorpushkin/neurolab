#include "stdafx.h"
#include "../../DataCreator.h"
#include "OperationsView.h"

#include "../../DataCollectionsDlg.h"
#include "../NewCollectionDlg.h"

// Global Operations Handlers
void OnNewCollection(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	CNewCollectionDlg mNewCollDlg;
	int res = mNewCollDlg.DoModal();
	if (res == IDOK)
	{		
		pDlg->mDataCollection.CreateCollection(mNewCollDlg.mCollectionName);
		pDlg->mDataCollection.GetCollectionGroup()->SetGroupName(mNewCollDlg.mCollectionName);

		pDlg->ShowCollection();
	} else
		pDlg->mCollectionProperties.UpdateState();
}

void OnLoadCollection(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Collection File v1.0|*.nlcfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		if (pDlg->mDataCollection.LoadCollection(mFileDlg.GetPathName()))
		{
			pDlg->csFileName = mFileDlg.GetPathName();

			pDlg->ShowCollection();
				
			AfxMessageBox("Collection was successfully loaded.");
		}
	}	

	pDlg->mCollectionProperties.UpdateState();
}

void OnSaveCollection(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	if (!pDlg->mDataCollection.IsCreated())
	{
		AfxMessageBox("Collection has not been created yet.");
       	pDlg->mCollectionProperties.UpdateState();
		return;
	} else
	{
		CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Collection File v1.0|*.nlcfile||");
		INT_PTR res = mFileDlg.DoModal();
		if (res == IDOK)
		{
			if (pDlg->mDataCollection.SaveCollection(mFileDlg.GetPathName()))
			{
				pDlg->csFileName = mFileDlg.GetPathName();
					
				AfxMessageBox("Collection was successfully saved.");			
			}
		}		
	} 

	pDlg->mCollectionProperties.UpdateState();
}

void OnCloseCollection(DWORD Param)
{
	CDataCollectionsDlg* pDlg = (CDataCollectionsDlg*)Param;

	pDlg->mCollectionProperties.UpdateState();
}