#include "stdafx.h"
#include "../../DataCreator.h"
#include "SolutionMain.h"

#include "../../DataCollectionsDlg.h"

// Solution Control Callback Command Handlers
void OnSelectIntro(DWORD Param)
{
	IParDef(pItemData, pData, Param, CDataCollectionsDlg*)
	
	pData->mCollectionProperties.ShowState(CString("Index"));
}

void OnSelectOperations(DWORD Param)
{
	IParDef(pItemData, pData, Param, CDataCollectionsDlg*)
	
	pData->mCollectionProperties.ShowState(CString("Process"));
}

void OnSelectCollection(DWORD Param)
{
	IParDef(pItemData, pData, Param, CDataCollectionsDlg*)
	
	pData->mCollectionProperties.ShowState(CString("Collection"));	
}

void OnSelectAbout(DWORD Param)
{
	IParDef(pItemData, pData, Param, CDataCollectionsDlg*)
	
	pData->mCollectionProperties.ShowState(CString("About"));	
}

