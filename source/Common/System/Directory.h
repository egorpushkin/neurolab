#pragma once

class CPath
{
public:
	static CString GetRelativePath(CString& ServerFile, CString& ClientFile)
	{
		CString tmServerFile = ServerFile;
		CString tmClientFile = ClientFile;

		tmServerFile.MakeUpper();
		tmClientFile.MakeUpper();

		if (tmServerFile.GetAt(0) != tmClientFile.GetAt(0))
			return ClientFile;

		CString tmServerFolder = GetFileFolder(tmServerFile);
		if (tmClientFile.Find(tmServerFolder) == 0)
			return ClientFile.Right(ClientFile.GetLength() - tmServerFolder.GetLength() - 1);

		return ClientFile;	
	}

	static CString RestoreFullName(CString& ServerFile, CString& RelativePath)
	{
		CString tmServerFile = ServerFile;
		CString tmRelativePath = RelativePath;

		tmServerFile.MakeUpper();
		tmRelativePath.MakeUpper();		

		if (tmRelativePath.GetAt(1) == ':')
			return RelativePath;

		CString tmServerFolder = GetFileFolder(ServerFile);
		CString resFullFileName = tmServerFolder + CString("\\") + RelativePath;
		return resFullFileName;
	}

	static CString GetFileFolder(CString& FileName)
	{
		int iSlashPosition = FileName.ReverseFind('\\');
		if (iSlashPosition == -1)
			return _T("");

		return FileName.Left(iSlashPosition);
	}

	static CString GetFileName(CString& FilePath)
	{
		int iSlashPosition = FilePath.ReverseFind('\\');
		if (iSlashPosition == -1)
			return _T("");

		return FilePath.Right(FilePath.GetLength() - iSlashPosition - 1);
	}
};

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