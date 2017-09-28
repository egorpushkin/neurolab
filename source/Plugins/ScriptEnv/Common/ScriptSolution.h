#pragma once

#include "Templates/Enumerator.h"
#include "CmnXML.h"

#include "SolutionItem.h"
#include "DataFileItem.h"
#include "BitmapItem.h"
#include "ProjectItem.h"
#include "SolutionSerialize.h"

class CScriptSolution :
	public IXMLStorageController
{
public:
	CScriptSolution()
		: csSolutionName(_T(""))
		, csFileName(_T(""))
		, bIsCreated(false)
	{	
	}

	~CScriptSolution()
	{
		DestroySolution();		
	}

	void CreateSolution(CString& SolutionName, CString& FileName, bool CreateEmptyFile = true)
	{
		if (bIsCreated)
			DestroySolution();

		SetSolutionName(SolutionName);
		SetFileName(FileName);

		if (CreateEmptyFile)
			CreateEmptySolutionFile();

		bIsCreated = true;
	}

	void DestroySolution()
	{
		bIsCreated = false;

		RELEASE_LIST(mSolutionItems, CSolutionItem*, true)
		RELEASE_LIST(mDataItems, CDataFileItem*, true)
		RELEASE_LIST(mBitmapItems, CBitmapItem*, true)
		RELEASE_LIST(mProjectItems, CProjectItem*, true)
	}

	void SetSolutionName(CString& SolutionName)
	{
		csSolutionName = SolutionName;
	}

	CString GetSolutionName()
	{
		return csSolutionName;
	}

	void SetFileName(CString& FileName)
	{
		csFileName = FileName;
	}

	CString GetFileName()
	{
		return csFileName;
	}

	bool IsCreated()
	{
		return bIsCreated;
	}

	CSolutionItem* AddItem(CString& FileName, CString& Description, bool DestroyExistingFile = true)
	{
		CSolutionItem* pItem = new CSolutionItem(FileName, Description, DestroyExistingFile);
		mSolutionItems.AddTail(pItem);

        return pItem;		
	}

	CDataFileItem* AddDataFile(CString& FileName)
	{
		CDataFileItem* pDataFileItem = new CDataFileItem(FileName);
		mDataItems.AddTail(pDataFileItem);

		return pDataFileItem;
	}

	CBitmapItem* AddBitmapFile(CString& FileName)
	{
		CBitmapItem* pBitmapItem = new CBitmapItem(FileName);
		mBitmapItems.AddTail(pBitmapItem);

		return pBitmapItem;
	}

	CProjectItem* AddProjectFile(CString& FileName)
	{
		CProjectItem* pProjectItem = new CProjectItem(FileName);
		mProjectItems.AddTail(pProjectItem);

		return pProjectItem;
	}

	bool SaveSolution()
	{		
		if (!bIsCreated)
			return false;

		CCommonXML tmXMLObject(csFileName);
		tmXMLObject.CreateInstance();
		
		if (Serialize(tmXMLObject.GetXMLDOMInstance(), false))
			if (tmXMLObject.SaveFile())
				return true;

		return false;
	}

	bool LoadSolution()
	{
		DestroySolution();

		CCommonXML tmXMLObject(csFileName);
		tmXMLObject.CreateInstance();

		if (tmXMLObject.LoadFile())
			if (Serialize(tmXMLObject.GetXMLDOMInstance(), true))
			{
				bIsCreated = true; 

				return true;
			}

		DestroySolution();
	
		return false;
	}

	ENUMERATOR(mSolutionItems, CSolutionItem*, CreateEnumerator, GetNextItem, posItems)
	ENUMERATOR(mDataItems, CDataFileItem*, CreateDataEnumerator, GetNextDataItem, posDataItems)
	ENUMERATOR(mBitmapItems, CBitmapItem*, CreateBitmapsEnumerator, GetNextBitmap, posBitmapItems)
	ENUMERATOR(mProjectItems, CProjectItem*, CreateProjectsEnumerator, GetNextProject, posProjectItems)

	int GetDataFilesCount()
	{
		return (int)mDataItems.GetCount();
	}

	void RemoveSolutionItem(CSolutionItem* pItem)
	{
		POSITION pos = mSolutionItems.Find(pItem);
		if (!pos)
			return;

		mSolutionItems.RemoveAt(pos);
		delete pItem;	
	}

	void RemoveDataItem(CDataFileItem* pItem)
	{
		POSITION pos = mDataItems.Find(pItem);
		if (!pos)
			return;

		mDataItems.RemoveAt(pos);
		delete pItem;	
	}

	void RemoveBitmap(CBitmapItem* pItem)
	{
		POSITION pos = mBitmapItems.Find(pItem);
		if (!pos)
			return;

		mBitmapItems.RemoveAt(pos);
		delete pItem;	
	}

	void RemoveProject(CProjectItem* pItem)
	{
		POSITION pos = mProjectItems.Find(pItem);
		if (!pos)
			return;

		mProjectItems.RemoveAt(pos);
		delete pItem;	
	}

	// IXMLStorageController declarations section
	bool Serialize(IXMLDOMDocument* pXMLDom, bool bIsLoad);

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CScriptSolution");
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IXMLStorageController:
			*ppvObject = (IXMLStorageController*)this;
			break;
		}
	}

private:
// Soluion FIle Operations
	void CreateEmptySolutionFile()
	{
		HANDLE hFile = CreateFile(csFileName,     // file to create
			GENERIC_WRITE,          // open for writing
			0,                      // do not share
			NULL,                   // default security
			CREATE_ALWAYS,          // overwrite existing
			FILE_ATTRIBUTE_NORMAL | // normal file
			FILE_FLAG_OVERLAPPED,   // asynchronous I/O
			NULL);                  // no attr. template

		CloseHandle(hFile);
	}

	bool			bIsCreated;
	CString			csSolutionName;
	CString			csFileName;
	
	CList<CSolutionItem*, CSolutionItem*> mSolutionItems;
	CList<CDataFileItem*, CDataFileItem*> mDataItems;
	CList<CBitmapItem*, CBitmapItem*> mBitmapItems;
	CList<CProjectItem*, CProjectItem*> mProjectItems;
};