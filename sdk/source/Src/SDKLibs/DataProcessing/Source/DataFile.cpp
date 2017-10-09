//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DataFile.cpp
//	Description: The CDataFile implementation file.

#include "../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

CDataFile::CDataFile()
	: bIsFileLoaded(false)
	, iInputSymbolsCount(0)
	, iInputSymbolLength(0)
	, iOutputSymbolsCount(0)
	, iOutputSymbolLength(0)
	, pInputSymbolsData(NULL)
	, pOutputSymbolsData(NULL)
	, numRef_(0)
{
}

CDataFile::CDataFile(LPCSTR FileName)
	: bIsFileLoaded(false)
{
	LoadFile(FileName);
}

CDataFile::~CDataFile()
{
	FreeLoadedData();
}

// IDataFactory implementations section
// Creation/Destruction entries
result CDataFile::LoadFile(LPCSTR FileName)
{
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeReadBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeLoad);
    return rSerialize;
}

result CDataFile::SaveToFile(LPCSTR FileName)
{
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeWriteBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeStore);
	return rSerialize;
}


void CDataFile::FreeLoadedData()
{
	if (bIsFileLoaded)
	{
		if (iInputSymbolsCount > 0)
		{
			for (uint i = 0;i < iInputSymbolsCount;i++)
				delete pInputSymbolsData[i];
			delete []pInputSymbolsData;
		}

		if (iOutputSymbolsCount > 0)
		{
			for (uint i = 0;i < iOutputSymbolsCount;i++)
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

void CDataFile::CreateNewFile(uint InputLength, uint OutputLength)
{
	FreeLoadedData();

	iInputSymbolsCount = 0;
	iInputSymbolLength = InputLength;
	iOutputSymbolsCount = 0;
	iOutputSymbolLength = OutputLength;

	bIsFileLoaded = true;	
}

// Data processing routines	
bool CDataFile::IsLoaded()
{
	return bIsFileLoaded;
}

uint CDataFile::GetInputSymbolsCount()
{
	return iInputSymbolsCount;
}

uint CDataFile::GetOutputSymbolsCount()
{
	return iOutputSymbolsCount;
}

uint CDataFile::GetInputSymbolLength()
{
	return iInputSymbolLength;
}

uint CDataFile::GetOutputSymbolLength()
{
	return iOutputSymbolLength;
}

IDataFactory* CDataFile::GetInputSymbol(uint Index)
{
	if (bIsFileLoaded && Index < iInputSymbolsCount)
		return pInputSymbolsData[Index];
	
	return NULL;
}

IDataFactory* CDataFile::GetOutputSymbol(uint Index)
{
	if (bIsFileLoaded && Index < iOutputSymbolsCount)
		return pOutputSymbolsData[Index];	

	return NULL;
}

void CDataFile::AddInputSymbol(float Value)
{
	CDataFactory** tmData = pInputSymbolsData;

	pInputSymbolsData = new CDataFactory*[iInputSymbolsCount + 1];
	for (uint i = 0;i < iInputSymbolsCount;i++)
		pInputSymbolsData[i] = tmData[i];

	pInputSymbolsData[iInputSymbolsCount] = new CDataFactory(iInputSymbolLength, Value);

	iInputSymbolsCount++;

	if (tmData)
		delete []tmData;
}

void CDataFile::AddOutputSymbol(float Value)
{
	CDataFactory** tmData = pOutputSymbolsData;

	pOutputSymbolsData = new CDataFactory*[iOutputSymbolsCount + 1];
	for (uint i = 0;i < iOutputSymbolsCount;i++)
		pOutputSymbolsData[i] = tmData[i];

	pOutputSymbolsData[iOutputSymbolsCount] = new CDataFactory(iOutputSymbolLength, Value);

	iOutputSymbolsCount++;

	if (tmData)
		delete []tmData;	
}

void CDataFile::AddInputSymbol(IDataFactory* pFactory)
{
	AddInputSymbol(0.0f);
	
	pInputSymbolsData[iInputSymbolsCount - 1]->SetData(
		pFactory->GetData(), pFactory->GetDataLength());
}

void CDataFile::AddOutputSymbol(IDataFactory* pFactory)
{
	AddOutputSymbol(0.0f);
	
	pOutputSymbolsData[iOutputSymbolsCount - 1]->SetData(
		pFactory->GetData(), pFactory->GetDataLength());	
}

void CDataFile::RemoveInputSymbol(uint Index)
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

		uint iIndex = 0;
		pInputSymbolsData = new CDataFactory*[iInputSymbolsCount - 1];
		for (uint i = 0;i < iInputSymbolsCount;i++)
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

void CDataFile::RemoveOutputSymbol(uint Index)
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

		uint iIndex = 0;
		pOutputSymbolsData = new CDataFactory*[iOutputSymbolsCount - 1];
		for (uint i = 0;i < iOutputSymbolsCount;i++)
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

// IStorageController implementations section
result CDataFile::Serialize(FILEDev& FileDev, bool Loading)
{
	StringA sFileInd("#NL_DATA_FILE");
	StringA sFileVersion("1.0.0.0a");

	if (Loading)
	{
		StringA sReadFileInd;
		StringA sReadFileVersion;

		FileDev.ReadStringA(sReadFileInd);
		FileDev.ReadStringA(sReadFileVersion);
		
		if (sFileInd != sReadFileInd || 
			sFileVersion != sReadFileVersion)
			return STG_E_INVALIDHEADER;

		FileDev.Read(&bIsFileLoaded, sizeof(bool));		
		if (bIsFileLoaded)
		{
			FileDev.Read(&iInputSymbolsCount, sizeof(int));
			FileDev.Read(&iInputSymbolLength, sizeof(int));
			FileDev.Read(&iOutputSymbolsCount, sizeof(int));
			FileDev.Read(&iOutputSymbolLength, sizeof(int));				

			if (iInputSymbolsCount > 0)
			{
				pInputSymbolsData = new CDataFactory*[iInputSymbolsCount];

				for (uint i = 0;i < iInputSymbolsCount;i++)
				{
					pInputSymbolsData[i] = new CDataFactory();
					pInputSymbolsData[i]->Serialize(FileDev, Loading);
				}
			} else
				pInputSymbolsData = NULL;

			if (iOutputSymbolsCount > 0)
			{
				pOutputSymbolsData = new CDataFactory*[iOutputSymbolsCount];

				for (uint i = 0;i < iOutputSymbolsCount;i++)
				{
					pOutputSymbolsData[i] = new CDataFactory();
					pOutputSymbolsData[i]->Serialize(FileDev, Loading);
				}
			} else
				pOutputSymbolsData = NULL;
		}

	} else
	{
		FileDev.WriteStringA(sFileInd);
		FileDev.WriteStringA(sFileVersion);

		FileDev.Write(&bIsFileLoaded, sizeof(bool));
		if (bIsFileLoaded)
		{
			FileDev.Write(&iInputSymbolsCount, sizeof(int));
			FileDev.Write(&iInputSymbolLength, sizeof(int));
			FileDev.Write(&iOutputSymbolsCount, sizeof(int));
			FileDev.Write(&iOutputSymbolLength, sizeof(int));	

			if (iInputSymbolsCount > 0 && pInputSymbolsData)
				for (uint i = 0;i < iInputSymbolsCount;i++)
					pInputSymbolsData[i]->Serialize(FileDev, Loading);

			if (iOutputSymbolsCount > 0 && pOutputSymbolsData)
				for (uint i = 0;i < iOutputSymbolsCount;i++)
					pOutputSymbolsData[i]->Serialize(FileDev, Loading);
		}
	}

	return S_OK;
}

// ICommon implementations section
ulong CDataFile::AddRef()
{
	return ++numRef_;						
}

ulong CDataFile::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CDataFile::GetClassString() const
{
    return _T("CDataFile");	
}

result CDataFile::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IDataFile*)this;
	}
	else if (refIID == IID_IDataFile)
	{
		*ppvObject = (IDataFile*)this;
	}
	else if (refIID == IID_IStorageController)
	{
		*ppvObject = (IStorageController*)this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)(IDataFile*)this)->AddRef();
	return S_OK;
}
