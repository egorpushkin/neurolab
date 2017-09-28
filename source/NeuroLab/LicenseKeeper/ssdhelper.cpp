/*
 * ssdhelper.cpp
 * Implementation for the SSD SDK security primitives
 * Emilio Guijarro Cameros
*/
#include "StdAfx.h"

#include "ssdhelper.h"

namespace SSDHelper {
	BOOL Initialize(LPCSTR lpszApplicationFolder, 
		LPCSTR lpszApplicationName, 
		LPCSTR lpszKeyfileName)
	{
		// Verification LicenseKeeperLib.dll library correction
		CString tmLicLibName = CString(lpszApplicationFolder) + 
			CString(_T("\\LicenseKeeperLib.dll"));

		CFile tmLicLibFile;
		if (!tmLicLibFile.Open(tmLicLibName, CFile::modeRead, NULL))
			return false;
		
		CString tmLicLibMD5 = CMD5Checksum::GetMD5(tmLicLibFile);

		tmLicLibFile.Close();

		if (tmLicLibMD5 != _T("35caf88df6ea37bc332644b2ee17a419"))
			return false;
	
		// Loading LicenseKeeperLib.dll library
		hMod = LoadLibrary("LicenseKeeperLib.dll");	
		if(hMod == NULL)
			return false;

		FuncType1 lpfnProc1 = (FuncType1)GetProcAddress(hMod, "IsLocked");
		FuncType2 lpfnProc2 = (FuncType2)GetProcAddress(hMod, "ExportKey");
		FuncType3 lpfnProc3 = (FuncType3)GetProcAddress(hMod, "Initialize");

		if (!lpfnProc1 || !lpfnProc2 || !lpfnProc3)
			return false;

		lpfnProc3(lpszApplicationName, lpszKeyfileName);

		return true;
	}

	BOOL IsUnlocked() {
		FuncType1 lpfnProc;
	
		lpfnProc = (FuncType1)GetProcAddress(hMod, "IsLocked");
	
		return lpfnProc();
	}

	void ExportKey(LPCSTR lpszFilename) {
		FuncType2 lpfnProc;
	
		lpfnProc = (FuncType2)GetProcAddress(hMod, "ExportKey");
	
		lpfnProc(lpszFilename);
	}

	BOOL Release() {
		if(hMod == NULL)
			return false;

		FreeLibrary(hMod);
	
		hMod = NULL;

		return true;
	}
}