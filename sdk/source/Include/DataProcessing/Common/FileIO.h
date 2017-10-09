//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: FileIO.h
//	Description: File device wrapper declaration.

#ifndef FILEIO_H__DATAPROCESSING__INCLUDED_
#define FILEIO_H__DATAPROCESSING__INCLUDED_

// Required definitions
#define	MAX_BUFFER_LENGTH			1024

// _FILE_Device implementation
struct _FILE_Device
{
	_FILE_Device()
		: pFileHandle_(NULL)
	{
	}

	_FILE_Device(LPCSTR fileName, LPCSTR mode)
		: pFileHandle_(NULL)
	{		
		Open(fileName, mode);
	}

	~_FILE_Device()
	{
		if (pFileHandle_)
			Close();
	}

	result Open(LPCSTR FileName, LPCSTR Mode)
	{
		if (pFileHandle_)
			Close();

		pFileHandle_ = fopen(FileName, Mode);
		if (!pFileHandle_)
			return STG_E_FILENOTFOUND;

		return S_OK;		
	}

	void Close()
	{
		if (pFileHandle_)
		{
			fclose(pFileHandle_);
			pFileHandle_ = NULL;
		}
	}

	// Data access functions
	size_t Read(void *pBuffer, size_t fragmentSize, size_t fragmentsCount = 1)
	{
		if (!pFileHandle_)
			return 0;
		return fread(pBuffer, fragmentSize, fragmentsCount, pFileHandle_);
	}

	size_t Write(const void* pBuffer, size_t fragmentSize, size_t fragmentsCount = 1)
	{
		if (!pFileHandle_)
			return 0;
		return fwrite(pBuffer, fragmentSize, fragmentsCount, pFileHandle_);
	}

	bool ReadStringA(char* pStringBuffer, uint maxBufferSize, uint skipCharacters = 1)
	{
		if (!pFileHandle_)
			return false;

		char* resultData = fgets(pStringBuffer, maxBufferSize, pFileHandle_);        

		if (!resultData)
			return false;

		if (skipCharacters > 0)
			pStringBuffer[strlen(pStringBuffer) - skipCharacters] = '\x0';

		return true;
	}

	bool ReadStringU(wchar_t* pStringBuffer, uint maxBufferSize, uint skipCharacters = 1)
	{
		if (!pFileHandle_)
			return false;

		wchar_t* resultData = fgetws(pStringBuffer, maxBufferSize, pFileHandle_);        

		if (!resultData)
			return false;

		if (skipCharacters > 0)
			pStringBuffer[wcslen(pStringBuffer) - skipCharacters] = L'\x0';

		return true;
	}

    bool ReadStringA(StringA& rStringBuffer, uint maxBufferSize = MAX_BUFFER_LENGTH, uint skipCharacters = 1)
	{
		if (!pFileHandle_)
			return false;

		char* bufferData = new char[maxBufferSize];
		char* resultData = fgets(bufferData, maxBufferSize, pFileHandle_);        
		
		if (resultData)
			rStringBuffer.append(bufferData);

		if (skipCharacters > 0)
			rStringBuffer.erase(rStringBuffer.length() - skipCharacters, skipCharacters);

		delete []bufferData;

		return (resultData != NULL);
	}

	bool ReadStringU(StringU& rStringBuffer, uint maxBufferSize = MAX_BUFFER_LENGTH, uint skipCharacters = 1)
	{
		if (!pFileHandle_)
			return false;

		wchar_t* bufferData = new wchar_t[maxBufferSize];
		wchar_t* resultData = fgetws(bufferData, maxBufferSize, pFileHandle_);        

		if (resultData)
			rStringBuffer.append(bufferData);

		if (skipCharacters > 0)
			rStringBuffer.erase(rStringBuffer.length() - skipCharacters, skipCharacters);

		delete []bufferData;

		return (resultData != NULL);
	}

	bool WriteStringA(const StringA& rStringBuffer, bool addEOL = true)
	{
		if (!pFileHandle_)
			return false;

		fputs(rStringBuffer.c_str(), pFileHandle_);        
		if (addEOL)
			fputs("\n", pFileHandle_);        
		
		return true;
	}

	bool WriteStringU(const StringU& rStringBuffer, bool addEOL = true)
	{
		if (!pFileHandle_)
			return false;

		fputws(rStringBuffer.c_str(), pFileHandle_);        
		if (addEOL)
			fputws(L"\n", pFileHandle_);        

		return true;
	}

	operator FILE*() 
	{
		return pFileHandle_; 
	} 

	long Tell()
	{
		return ftell(pFileHandle_);
	}

	int GetPos(fpos_t* position)
	{
		return fgetpos(pFileHandle_, position);
	}
	
private:
	// Private (locked) device operators
	_FILE_Device(const _FILE_Device&);
    const _FILE_Device& operator =(const _FILE_Device&);

	// Private device data
	FILE*				pFileHandle_;
};

//
// File system core definitions
//

#define ModeLoad					true
#define ModeStore					false

#define ModeRead					"r"
#define ModeWrite					"w"
#define ModeReadBinary				"rb"
#define ModeWriteBinary				"wb"

// 
// File Device user type declaration
//

typedef _FILE_Device				FILEDev;
typedef _FILE_Device&				FILEDevRef;

//
// Unicode macros for File Device
//

#ifdef _UNICODE
#define ReadString					ReadStringU
#define WriteString					WriteStringU
#else
#define ReadString					ReadStringA
#define WriteString					WriteStringA
#endif

#endif // !CMNFILEIO_H__DATAPROCESSING__INCLUDED_
