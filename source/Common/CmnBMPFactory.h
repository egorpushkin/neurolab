#pragma once

#include "interface_idds.h"

#include "CmnObjects.h"
#include "CmnStorage.h"

interface IBMPFactory : public IObject
{
	virtual bool			LoadBMPFile(CString& FileName) = 0;
	virtual void			SaveBMPFile(CString& FileName) = 0;
};

class CBMPFactory : 
	public CDataFactory,
	public IBMPFactory
{
public:
	// IBMPFactory implementations section
	virtual bool LoadBMPFile(CString& FileName)
	{
		bool bRet = false;

		CFile cfLoadFile;
		if (cfLoadFile.Open(FileName, CFile::modeRead, NULL))
		{
			CArchive ar(&cfLoadFile, CArchive::load);			
			
			bRet = Serialize(ar);

			ar.Close();
			cfLoadFile.Close();
		} 

		return bRet;
	}

	virtual void SaveBMPFile(CString& FileName)
	{	
	}

	// IStorageController implementations section
	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			BITMAPFILEHEADER bitmapFileHeader;
			BITMAPINFOHEADER bitmapInfoHeader;

			CFile* pFile = ar.GetFile();

			pFile->Read(&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
			
			if (bitmapFileHeader.bfType != 0x4D42)
				return false;

			pFile->Read(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

			unsigned char* pszImageData = new unsigned char[bitmapInfoHeader.biSizeImage];

			pFile->Seek(bitmapFileHeader.bfOffBits, SEEK_SET);
			pFile->Read(pszImageData, bitmapInfoHeader.biSizeImage);

			if (bitmapInfoHeader.biBitCount > 8)
			{
				delete[] pszImageData;
				return false;
			}

			int iImageLength = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight;
			CreateFactory(iImageLength);
			for (int i = 0;i < iImageLength;i++)
			{
				float fValue = GetFloatOfBitData(pszImageData, i, &bitmapInfoHeader);				
				SetItemData(i, fValue);
			}

			delete[] pszImageData;
		} else
		{
		}

		return true;
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CBMPFactory");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IBMPFactory:
			*ppvObject = (IBMPFactory*)this;
			break;
		case IDD_IDataFactory:
			*ppvObject = (IDataFactory*)this;
			break;
		case IDD_IStorageController:
			*ppvObject = (IStorageController*)this;
			break;
		}
	}

private:
	float GetFloatOfBitData(unsigned char* pszData, int iIndex, BITMAPINFOHEADER* pHeader)
	{
		int iYOffset = pHeader->biHeight - (iIndex / pHeader->biWidth) - 1;
		int iXOffset = iIndex % pHeader->biWidth;

		int iLineDWORDs = ((pHeader->biWidth * pHeader->biBitCount - 1) / 64) + 1;
		int iBitLineWidth = iLineDWORDs * 64;

		int iBitOffset = iYOffset * iBitLineWidth + iXOffset * pHeader->biBitCount;
              		
		int iByteIndex = iBitOffset / (8 / pHeader->biBitCount);
		unsigned char cData = pszData[iByteIndex];

		int iByteOffset = 7 - (iBitOffset % (8 / pHeader->biBitCount));

		unsigned char cShiftedData = cData >> iByteOffset;
		cShiftedData = cShiftedData << (8 - pHeader->biBitCount);
		cShiftedData = cShiftedData >> (8 - pHeader->biBitCount);
		
		return cShiftedData*1.0f;
	}
};
