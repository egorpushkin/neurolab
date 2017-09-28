#pragma once

class CDirectoryEnumerator
{
public:
	CDirectoryEnumerator(CString& csPath)
	{
		csDirectoryPath = csPath;
	}

	void EnumerateDirectoryEntries()
	{
		WIN32_FIND_DATA fdFileData; 
		HANDLE hSearch; 

		hSearch = FindFirstFile(csDirectoryPath, &fdFileData); 
		if (hSearch == INVALID_HANDLE_VALUE) 
			return;

		while (true) 
		{
			mFilesList.AddTail(fdFileData.cFileName);

			if (!FindNextFile(hSearch, &fdFileData)) 
				break;
		} 

		FindClose(hSearch);
	}

	CString							csDirectoryPath;
	CList<CString, CString>			mFilesList;
};