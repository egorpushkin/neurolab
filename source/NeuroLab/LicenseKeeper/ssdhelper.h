/*
 * ssdhelper.h
 * Declaration for the SSD SDK security primitives
 * Emilio Guijarro Cameros
*/
	
#ifndef _SSDHELPER_
#define _SSDHELPER_

#include <windows.h>

#include "MD5Checksum\MD5Checksum.h"

namespace SSDHelper {
	typedef bool (*FuncType1)(); 
	typedef void (*FuncType2)(LPCTSTR); 
	typedef void (*FuncType3)(LPCTSTR, LPCTSTR); 
	
	static HMODULE hMod;

	BOOL Initialize(LPCSTR lpszApplicationFolder, 
		LPCSTR lpszApplicationName, 
		LPCSTR lpszKeyfileName);
	void ExportKey(LPCSTR lpszFilename);
	BOOL IsUnlocked();
	BOOL Release();
}

#endif