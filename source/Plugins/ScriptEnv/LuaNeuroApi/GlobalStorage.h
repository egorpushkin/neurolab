#pragma once

// Neuro Laboratory core object model headers
#include "System\Directory.h"
#include "CmnLog.h"
#include "CmnDataFile.h"
#include "CmnFactory.h"
#include "CmnPGMBitmap.h"

#include "..\Common\ScriptSolution.h"

#include "..\NetworkImporter\ImportManagerComponent.h"

#include "../ScriptEnv.h"
#include "Charting/ui/ChartsViewDlg.h"

class CLuaStorage_GlobalEnvironment
{
public:
	static CString			csCurrentDirectory;
	
	static CString			csSolutionDirectory;
	static CString			csScriptDirectory;
	static CString			csAppDirectory;
};

class CLuaStorage_LogProvider
{
public:
	static ILogProvider*	pLogProvider;
	static int				iCurPercentage;
};

class CLuaStorage_NetworkProcessor
{
public:
    static INetworkProcessor* pNetworkProcessor;
    static IElementsCollection* pElementsCollection;
};

class CLuaStorage_DataFile
{
public:
	CDataFile				mDataFile;
	CString					csFileName;
};

class CLuaStorage_Bitmap
{
public:
	CPGMBitmap				mPGMBitmap;
	CString					csFileName;
};

class CLuaStorage_Project
{
public:
	IImportManager*			pImportManager;
	CString					csFileName;
};

class CLuaStorage_Solution
{
public:
	static CScriptSolution*	pSolution;	
	static CImportManagerComponent*	pImportManagerComponent;	
	
	static CList<CLuaStorage_DataFile*, CLuaStorage_DataFile*> mDataFiles;
	static CList<CLuaStorage_Bitmap*, CLuaStorage_Bitmap*> mBitmapFiles;
	static CList<CLuaStorage_Project*, CLuaStorage_Project*> mProjectFiles;
	
	static void FillFilesList()
	{
		if (!pSolution)
			return;

		ReleaseFilesList();

		pSolution->CreateDataEnumerator();
		while (CDataFileItem* pDataFileItem = pSolution->GetNextDataItem())
		{
			CLuaStorage_DataFile* pDataFile = new CLuaStorage_DataFile;
			
			pDataFile->csFileName = pDataFileItem->GetFileName();
			pDataFile->mDataFile.LoadFile(pDataFileItem->GetFileName());

			mDataFiles.AddTail(pDataFile);
		}

		pSolution->CreateBitmapsEnumerator();
		while (CBitmapItem* pBitmapItem = pSolution->GetNextBitmap())
		{
			CLuaStorage_Bitmap* pBitmap = new CLuaStorage_Bitmap;
			
			pBitmap->csFileName = pBitmapItem->GetFileName();
			pBitmap->mPGMBitmap.LoadPGMBitmap(pBitmapItem->GetFileName());

			mBitmapFiles.AddTail(pBitmap);
		}

		if (pImportManagerComponent->IsLoaded())		
		{
			pSolution->CreateProjectsEnumerator();
			while (CProjectItem* pProjectItem = pSolution->GetNextProject())
			{
				CLuaStorage_Project* pProject = new CLuaStorage_Project;
				
				pProject->csFileName = pProjectItem->GetFileName();
				pProject->pImportManager = pImportManagerComponent->GetImportManager();
				pProject->pImportManager->LoadNLProject(pProjectItem->GetFileName());

				mProjectFiles.AddTail(pProject);
			}					
		}
	}

	static void ReleaseFilesList()
	{
		RELEASE_LIST(mDataFiles, CLuaStorage_DataFile*, true)
		RELEASE_LIST(mBitmapFiles, CLuaStorage_Bitmap*, true)

		while (mProjectFiles.GetCount() > 0)
		{
			CLuaStorage_Project* pProject = mProjectFiles.GetHead();
			mProjectFiles.RemoveHead();

			pImportManagerComponent->ReleaseImportManager(pProject->pImportManager);

			delete pProject;
		}
	}

	static CString GetDataFileName(int iIndex)
	{
		POSITION pos = mDataFiles.FindIndex(iIndex);
		if (!pos)
			return _T("");

		CLuaStorage_DataFile* pItem = mDataFiles.GetAt(pos);
		if (!pItem)
			return _T("");

		CString tmFileName = CPath::GetFileName(pItem->csFileName);
		int iDotPos = tmFileName.Find('.');
		tmFileName = tmFileName.Left(iDotPos);
        
		return tmFileName;
	}

	static IDataFile* GetDataFile(int iIndex)
	{
		POSITION pos = mDataFiles.FindIndex(iIndex);
		if (!pos)
			return NULL;

		CLuaStorage_DataFile* pItem = mDataFiles.GetAt(pos);
		
		return GetItemDataFile(pItem);
	}

	static IDataFile* GetDataFile(CString& FileName)
	{
		for (POSITION pos = mDataFiles.GetHeadPosition();pos;)
		{			
			CLuaStorage_DataFile* pItem = mDataFiles.GetNext(pos);			
			CString tmFileName = CPath::GetFileName(pItem->csFileName);
			
			FileName.MakeUpper();
			tmFileName.MakeUpper();
			if (tmFileName.Find(FileName) != -1)
				return GetItemDataFile(pItem);								
		}

        return NULL;
	}

	static IDataBitmap* GetBitmap(CString& FileName)
	{
		for (POSITION pos = mBitmapFiles.GetHeadPosition();pos;)
		{			
			CLuaStorage_Bitmap* pItem = mBitmapFiles.GetNext(pos);			
			CString tmFileName = CPath::GetFileName(pItem->csFileName);
			
			FileName.MakeUpper();
			tmFileName.MakeUpper();
			if (tmFileName.Find(FileName) != -1)
				return GetItemBitmap(pItem);								
		}

        return NULL;	
	}

	static IImportManager* GetProject(CString& FileName)
	{
		for (POSITION pos = mProjectFiles.GetHeadPosition();pos;)
		{			
			CLuaStorage_Project* pItem = mProjectFiles.GetNext(pos);			
			CString tmFileName = CPath::GetFileName(pItem->csFileName);
			
			FileName.MakeUpper();
			tmFileName.MakeUpper();
			if (tmFileName.Find(FileName) != -1)
				return pItem->pImportManager;
		}

        return NULL;	
	}

private:
	static IDataFile* GetItemDataFile(CLuaStorage_DataFile* pItem)
	{
		if (!pItem->mDataFile.IsLoaded())
			return NULL;

		IDataFile* pDataFile = NULL;
		pItem->mDataFile.QueryInterface(IDD_IDataFile, (void**)&pDataFile);

        return pDataFile;	
	}

	static IDataBitmap* GetItemBitmap(CLuaStorage_Bitmap* pItem)
	{
		if (!pItem->mPGMBitmap.IsLoaded())
			return NULL;

		IDataBitmap* pDataBitmap = NULL;
		pItem->mPGMBitmap.QueryInterface(IDD_IDataBitmap, (void**)&pDataBitmap);

        return pDataBitmap;	
	}
};

template <class ObjectType, bool RemoveInstance> class CLuaStorage_ObjectsContainer
{
public:
	static bool RemoveObject(ObjectType pDataFactory)
	{
		POSITION pos = mObjectsList.Find(pDataFactory);
		if (!pos)
			return false;

		mObjectsList.RemoveAt(pos);
		if (RemoveInstance)
			delete pDataFactory;

		return true;
	}

	static void AddObject(ObjectType pDataFactory)
	{
		mObjectsList.AddTail(pDataFactory);
	}    

	static void ReleaseContainer()
	{
		RELEASE_LIST(mObjectsList, ObjectType, true)
	}

	static CList<ObjectType, ObjectType> mObjectsList;
};

#define CLuaStorage_FactoriesContainer CLuaStorage_ObjectsContainer<IDataFactory*, true>
#define CLuaStorage_DataFilesContainer CLuaStorage_ObjectsContainer<IDataFile*, true>
#define CLuaStorage_BitmapsContainer CLuaStorage_ObjectsContainer<IDataBitmap*, true>
#define CLuaStorage_ChartsContainer CLuaStorage_ObjectsContainer<CChartsViewDlg*, true>
