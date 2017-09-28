#pragma once

#include <iostream>
#include <fstream>

using namespace std; 

#include "interface_idds.h"

#include "CmnDataFactory.h"

interface IPGMFactory : public IObject
{
	virtual bool			LoadPGMFile(CString& FileName) = 0;
	virtual bool			SavePGMFile(CString& FileName) = 0;
};

class CPGMFactory : 
	public CDataFactory,
	public IPGMFactory
{
public:
	// IPGMFactory implementations section
	virtual bool LoadPGMFile(CString& FileName)
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

	virtual bool SavePGMFile(CString& FileName)
	{	
		bool bRet = false;

		CFile cfLoadFile;
		if (cfLoadFile.Open(FileName, CFile::modeCreate | CFile::modeWrite))
		{
			CArchive ar(&cfLoadFile, CArchive::store);			
			
			bRet = Serialize(ar);

			ar.Close();
			cfLoadFile.Close();
		} 

		return bRet;
	}

	// IStorageController implementations section
	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			bool			error;
			
			int				xsize;
			int				ysize;
			unsigned char	maxg;
			
			error = PGMBReadHeader(ar, &xsize, &ysize, &maxg);
			if (!error)
				return false;

			CreateFactory(xsize * ysize);

			error = PGMReadData(ar, xsize, ysize);
			if (!error)
			{
				ReleaseFactory();
				return false;
			}
		} else
		{

		}

		return true;
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CPGMFactory");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IPGMFactory:
			*ppvObject = (IPGMFactory*)this;
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

	bool PGMBReadHeader(CArchive& ar, int* xsize, int* ysize, unsigned char* maxg)
	{
		int				count;
		char			line[255];
		int				maxg2;
		char*			next;
		int				step;
		int				width;
		char			word[255];

		step = 0;

		while (1)
		{
			LPTSTR pDataBuf = ar.ReadString(line, sizeof(line));
			
			if (!pDataBuf)
				return false;

			next = line;
		
			if (line[0] == '#')
				continue;
	
			if (step == 0)
			{
				count = sscanf(next, "%s%n", word, &width);
				if (count == EOF)
					continue;
				
				next = next + width;
				if (strcmp(word, "P5") != 0 && strcmp(word, "p5") != 0)
					return false;
	
				step = 1;
			}

			if ( step == 1 )
			{
				count = sscanf(next, "%d%n", xsize, &width);
				next = next + width;
				
				if (count == EOF)
					continue;
				
				step = 2;
			}

			if (step == 2)
			{
				count = sscanf(next, "%d%n", ysize, &width);
				next = next + width;

				if (count == EOF)
					continue;
		
				step = 3;
			}

			if (step == 3)
			{
				count = sscanf(next, "%d%n", &maxg2, &width);
				*maxg = (unsigned char)maxg2;
				next = next + width;
				
				if (count == EOF)
					continue;
				
				break;
			}
		}

		return true;
	} 

	bool PGMReadData(CArchive& ar, int xsize, int ysize)
	{
		unsigned char		c;
		bool				error;
		int					i;
		float*				indexdata;
		int					j;

		indexdata = GetData();

		for (j = 0; j < ysize; j++)
			for (i = 0; i < xsize; i++)
			{
				int iread = ar.Read(&c, 1);
				*indexdata = (float)c;
				indexdata = indexdata + 1;
				
				if (iread < 1)
					return false;
			}

		return true;
	} 
};
