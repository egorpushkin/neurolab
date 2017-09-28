#pragma once

#include "interface_idds.h"

#include "CmnObjects.h"
#include "CmnStorage.h"
#include "CmnDataFactory.h"

interface IDataFile : public IObject
{
	// Creation/Destruction entries
	virtual bool			LoadFile(CString& FileName) = 0;
	virtual void			FreeLoadedData() = 0;
	virtual bool			SaveToFile(CString& FileName) = 0;
	virtual void			CreateNewFile(int InputLength, int OutputLength) = 0; 

	// Data processing routines
	virtual bool			IsLoaded() = 0;

	virtual int				GetInputSymbolsCount() = 0;
	virtual int				GetOutputSymbolsCount() = 0;

	virtual int				GetInputSymbolLength() = 0;
	virtual int				GetOutputSymbolLength() = 0;

	virtual IDataFactory*	GetInputSymbol(int Index) = 0;
	virtual IDataFactory*	GetOutputSymbol(int Index) = 0;

	virtual void			AddInputSymbol(float Value) = 0;
	virtual void			AddOutputSymbol(float Value) = 0;

	virtual void			AddInputSymbol(IDataFactory* pFactory) = 0;
	virtual void			AddOutputSymbol(IDataFactory* pFactory) = 0;

	virtual void			RemoveInputSymbol(int Index) = 0;
	virtual void			RemoveOutputSymbol(int Index) = 0;
};

class CDataFile :
	public IDataFile,
	public IStorageController
{
public:
	CDataFile()
		: bIsFileLoaded(false)
		, iInputSymbolsCount(0)
		, iInputSymbolLength(0)
		, iOutputSymbolsCount(0)
		, iOutputSymbolLength(0)
		, pInputSymbolsData(NULL)
		, pOutputSymbolsData(NULL)
	{
	}

	CDataFile(CString& FileName)
		: bIsFileLoaded(false)
	{
		LoadFile(FileName);
	}

	~CDataFile()
	{
		FreeLoadedData();
	}

	// IStorageController implementations section
	virtual bool Serialize(CArchive& ar)
	{
		CString csFileInd("#NL_DATA_FILE");
		CString csFileVersion("1.0.0.0a");
	
		if (ar.IsLoading())
		{
			CString csReadFileInd;
			CString csReadFileVersion;
		
			ar.ReadString(csReadFileInd);
			ar.ReadString(csReadFileVersion);

			if (csFileInd != csReadFileInd || csFileVersion != csReadFileVersion)
				return false;

			ar.Read(&bIsFileLoaded, sizeof(bool));
			if (bIsFileLoaded)
			{
				ar.Read(&iInputSymbolsCount, sizeof(int));
				ar.Read(&iInputSymbolLength, sizeof(int));
				ar.Read(&iOutputSymbolsCount, sizeof(int));
				ar.Read(&iOutputSymbolLength, sizeof(int));				

				if (iInputSymbolsCount > 0)
				{
					pInputSymbolsData = new CDataFactory*[iInputSymbolsCount];

					for (int i = 0;i < iInputSymbolsCount;i++)
					{
						pInputSymbolsData[i] = new CDataFactory();
						pInputSymbolsData[i]->Serialize(ar);
					}
				} else
					pInputSymbolsData = NULL;

				if (iOutputSymbolsCount > 0)
				{
					pOutputSymbolsData = new CDataFactory*[iOutputSymbolsCount];

					for (int i = 0;i < iOutputSymbolsCount;i++)
					{
						pOutputSymbolsData[i] = new CDataFactory();
						pOutputSymbolsData[i]->Serialize(ar);
					}
				} else
					pOutputSymbolsData = NULL;
			}
		
		} else
		{
			ar.WriteString(csFileInd); ar.Write("\n",1);
			ar.WriteString(csFileVersion); ar.Write("\n",1);			

			ar.Write(&bIsFileLoaded, sizeof(bool));
			if (bIsFileLoaded)
			{
				ar.Write(&iInputSymbolsCount, sizeof(int));
				ar.Write(&iInputSymbolLength, sizeof(int));
				ar.Write(&iOutputSymbolsCount, sizeof(int));
				ar.Write(&iOutputSymbolLength, sizeof(int));	

				if (iInputSymbolsCount > 0 && pInputSymbolsData)
					for (int i = 0;i < iInputSymbolsCount;i++)
						pInputSymbolsData[i]->Serialize(ar);

				if (iOutputSymbolsCount > 0 && pOutputSymbolsData)
					for (int i = 0;i < iOutputSymbolsCount;i++)
						pOutputSymbolsData[i]->Serialize(ar);
			}		
		}

		return true;
	}

	// IDataFactory implementations section
	// Creation/Destruction entries
	virtual bool LoadFile(CString& FileName)
	{
		CFile tmFile;
		if (tmFile.Open(FileName, CFile::modeRead))
		{
			FreeLoadedData();

			CArchive ar(&tmFile, CArchive::load);
			bool bRet = Serialize(ar);
			ar.Close();

			return bRet;
		}
		return false;
	}

	virtual void FreeLoadedData()
	{
		if (bIsFileLoaded)
		{
			if (iInputSymbolsCount > 0)
			{
				for (int i = 0;i < iInputSymbolsCount;i++)
					delete pInputSymbolsData[i];
				delete []pInputSymbolsData;
			}

			if (iOutputSymbolsCount > 0)
			{
				for (int i = 0;i < iOutputSymbolsCount;i++)
					delete pOutputSymbolsData[i];
				delete []pOutputSymbolsData;
			}

			pInputSymbolsData = NULL;
			pOutputSymbolsData = NULL;

			iInputSymbolsCount = 0;
			iInputSymbolLength = 0;
			iOutputSymbolsCount = 0;
			iOutputSymbolLength = 0;
		
			bIsFileLoaded = false;
		}	
	}

	virtual bool SaveToFile(CString& FileName)
	{
		bool bRet;

		CFile tmFile;
		if (tmFile.Open(FileName, CFile::modeCreate | CFile::modeWrite))
		{
			CArchive ar(&tmFile, CArchive::store);
			bRet = Serialize(ar);
			ar.Close();
		} else
			return false;

		return bRet;
	}

	virtual void CreateNewFile(int InputLength, int OutputLength)
	{
		FreeLoadedData();

		iInputSymbolsCount = 0;
		iInputSymbolLength = InputLength;
		iOutputSymbolsCount = 0;
		iOutputSymbolLength = OutputLength;

		bIsFileLoaded = true;	
	}

	// Data processing routines	
	virtual bool IsLoaded()
	{
		return bIsFileLoaded;
	}

	virtual int GetInputSymbolsCount()
	{
		return iInputSymbolsCount;
	}

	virtual int	GetOutputSymbolsCount()
	{
		return iOutputSymbolsCount;
	}

	virtual int	GetInputSymbolLength()
	{
		return iInputSymbolLength;
	}

	virtual int	GetOutputSymbolLength()
	{
		return iOutputSymbolLength;
	}

	virtual IDataFactory* GetInputSymbol(int Index)
	{
		if (bIsFileLoaded && Index < iInputSymbolsCount)
			return pInputSymbolsData[Index];
		
		return NULL;
	}

	virtual IDataFactory* GetOutputSymbol(int Index)
	{
		if (bIsFileLoaded && Index < iOutputSymbolsCount)
			return pOutputSymbolsData[Index];	

		return NULL;
	}

	virtual void AddInputSymbol(float Value)
	{
		CDataFactory** tmData = pInputSymbolsData;

		pInputSymbolsData = new CDataFactory*[iInputSymbolsCount + 1];
		for (int i = 0;i < iInputSymbolsCount;i++)
			pInputSymbolsData[i] = tmData[i];

		pInputSymbolsData[iInputSymbolsCount] = new CDataFactory(iInputSymbolLength, Value);

		iInputSymbolsCount++;

		if (tmData)
			delete []tmData;
	}

	virtual void AddOutputSymbol(float Value)
	{
		CDataFactory** tmData = pOutputSymbolsData;

		pOutputSymbolsData = new CDataFactory*[iOutputSymbolsCount + 1];
		for (int i = 0;i < iOutputSymbolsCount;i++)
			pOutputSymbolsData[i] = tmData[i];

		pOutputSymbolsData[iOutputSymbolsCount] = new CDataFactory(iOutputSymbolLength, Value);

		iOutputSymbolsCount++;

		if (tmData)
			delete []tmData;	
	}

	virtual void AddInputSymbol(IDataFactory* pFactory)
	{
		AddInputSymbol(0.0f);
		
		pInputSymbolsData[iInputSymbolsCount - 1]->SetData(
			pFactory->GetData(), pFactory->GetDataLength());
	}

	virtual void AddOutputSymbol(IDataFactory* pFactory)
	{
		AddOutputSymbol(0.0f);
		
		pOutputSymbolsData[iOutputSymbolsCount - 1]->SetData(
			pFactory->GetData(), pFactory->GetDataLength());	
	}

	virtual void RemoveInputSymbol(int Index)
	{
		if (iInputSymbolsCount == 0)
			return;
		if (iInputSymbolsCount == 1)
		{
			delete pInputSymbolsData[0];
			delete pInputSymbolsData;

			pInputSymbolsData = NULL;

			iInputSymbolsCount = 0;		
		} else 
		{		 
			CDataFactory** tmData = pInputSymbolsData;

			int iIndex = 0;
			pInputSymbolsData = new CDataFactory*[iInputSymbolsCount - 1];
			for (int i = 0;i < iInputSymbolsCount;i++)
				if (i != Index)
				{
					pInputSymbolsData[iIndex] = tmData[i];
					iIndex++;
				} else
					delete tmData[i];

			iInputSymbolsCount--;
	
			delete []tmData;	
		}
	}

	virtual void RemoveOutputSymbol(int Index)
	{
		if (iOutputSymbolsCount == 0)
			return;
		if (iOutputSymbolsCount == 1)
		{
			delete pOutputSymbolsData[0];
			delete pOutputSymbolsData;

			pOutputSymbolsData = NULL;

			iOutputSymbolsCount = 0;			
		} else
		{
			CDataFactory** tmData = pOutputSymbolsData;

			int iIndex = 0;
			pOutputSymbolsData = new CDataFactory*[iOutputSymbolsCount - 1];
			for (int i = 0;i < iOutputSymbolsCount;i++)
				if (i != Index)
				{
					pOutputSymbolsData[iIndex] = tmData[i];
					iIndex++;
				} else
					delete tmData[i];

			iOutputSymbolsCount--;

			delete []tmData;			
		}
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CDataFile");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IDataFile:
			*ppvObject = (IDataFile*)this;
			break;
		case IDD_IStorageController:
			*ppvObject = (IStorageController*)this;
			break;
		}
	}

private:
	bool			bIsFileLoaded;

	int				iInputSymbolsCount;
	int				iInputSymbolLength;
	int				iOutputSymbolsCount;
	int				iOutputSymbolLength;

	CDataFactory**	pInputSymbolsData;
	CDataFactory**	pOutputSymbolsData;
};