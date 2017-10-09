#pragma once

#include "../CmnDataFactory.h"
#include "../CmnPGMFactory.h"
#include "../CmnBMPFactory.h"

class CCollectionConverterOperation_LoadImage
{
public:
	static IDataFactory* LoadImage(
		CString& FileName)
	{
		CString tmExtension = GetFileExtension(FileName);
		tmExtension.MakeUpper();

		if (tmExtension == _T("PGM"))
		{
			CPGMFactory* pPGMFactory = new CPGMFactory;
			pPGMFactory->LoadPGMFile(FileName);

			IDataFactory* pFactory = NULL;
			pPGMFactory->QueryInterface(IDD_IDataFactory, (void**)&pFactory);
		
			return pFactory;
		} 
		if (tmExtension == _T("BMP"))
		{
			CBMPFactory* pBMPFactory = new CBMPFactory;
			pBMPFactory->LoadBMPFile(FileName);

			IDataFactory* pFactory = NULL;
			pBMPFactory->QueryInterface(IDD_IDataFactory, (void**)&pFactory);
		
			return pFactory;			
		}
	
		return NULL;
	}

	static CString GetFileExtension(CString& FileName)
	{
		int iDotPosition = FileName.ReverseFind('.');		
		return FileName.Right(FileName.GetLength() - iDotPosition - 1);
	}
};