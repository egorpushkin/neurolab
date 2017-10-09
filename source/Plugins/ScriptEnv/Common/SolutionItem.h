#pragma once

class CSolutionItem : 
	public IObject
{
public:
	CSolutionItem()
		: csFileName(_T(""))
		, csDescription(_T(""))
	{	
	}
	CSolutionItem(CString& FileName, CString& Description, bool DestroyExistingFile = true)
		: csFileName(FileName)
		, csDescription(Description)
	{
		if (DestroyExistingFile)
			CreateEmptyFile();
	}

	void SetFileName(CString& FileName)
	{
		csFileName = FileName;
	}

	CString	GetFileName()
	{
		return csFileName;
	}

	void SetDescription(CString& Description)
	{
		csDescription = Description;
	}

	CString	GetDescription()
	{
		return csDescription;
	}

	void UpdateScriptFileContent(CString& FileContent)
	{
		HANDLE hFile = CreateFile(csFileName,     // file to create
			GENERIC_WRITE,          // open for writing
			0,                      // do not share
			NULL,                   // default security
			CREATE_ALWAYS,          // overwrite existing
			FILE_ATTRIBUTE_NORMAL,  // normal file
			NULL);                  // no attr. template

		DWORD dwBytesWritten;
		BOOL bRet = WriteFile(hFile, FileContent, FileContent.GetLength(),
			&dwBytesWritten, NULL);

		CloseHandle(hFile);
	}

	CString GetScriptFileContent()
	{
		HANDLE hFile = CreateFile(csFileName,    // file to open
			GENERIC_READ,          // open for reading
			FILE_SHARE_READ,       // share for reading
			NULL,                  // default security
			OPEN_EXISTING,         // existing file only
			FILE_ATTRIBUTE_NORMAL, // normal file
			NULL);                 // no attr. template

		DWORD dwBytesRead;

		int iBufferSize = 1024*1024;
		char* pszBuffer = new char[iBufferSize];
		
        ReadFile(hFile, pszBuffer, iBufferSize, &dwBytesRead, NULL);
		pszBuffer[dwBytesRead] = 0;
	
		CloseHandle(hFile);	

		CString tmFileContent(pszBuffer);		
		delete []pszBuffer;

		return tmFileContent;
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CSolutionItem");
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
// Script FIle Operations
	void CreateEmptyFile()
	{
		HANDLE hFile = hFile = CreateFile(csFileName,     // file to create
			GENERIC_WRITE,          // open for writing
			0,                      // do not share
			NULL,                   // default security
			CREATE_ALWAYS,          // overwrite existing
			FILE_ATTRIBUTE_NORMAL | // normal file
			FILE_FLAG_OVERLAPPED,   // asynchronous I/O
			NULL);                  // no attr. template

		CloseHandle(hFile);
	}

	CString			csFileName;
	CString			csDescription;
};