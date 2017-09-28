//	This code is a part of Data Processing SDK.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CmnBMPFormat.h
//	Description: The .

#ifndef CMNBMPFORMAT_H__DATAPROCESSING__INCLUDED_
#define CMNBMPFORMAT_H__DATAPROCESSING__INCLUDED_

/************************************************************************

The BITMAPFILEHEADER structure contains information about the type, 
size, and layout of a file that contains a DIB. 

************************************************************************/

#ifndef WINGDIAPI

typedef struct tagBITMAPFILEHEADER { 
	word					bfType; 
	dword					bfSize; 
	word					bfReserved1; 
	word					bfReserved2; 
	dword					bfOffBits; 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

/************************************************************************

	The BITMAPINFOHEADER structure contains information about the 
	dimensions and color format of a DIB. 

************************************************************************/

typedef struct tagBITMAPINFOHEADER {
	dword					biSize; 
	long					biWidth; 
	long					biHeight; 
	word					biPlanes; 
	word					biBitCount; 
	dword					biCompression; 
	dword					biSizeImage; 
	long					biXPelsPerMeter; 
	long					biYPelsPerMeter; 
	dword					biClrUsed; 
	dword					biClrImportant; 
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

#endif // !WINGDIAPI

#endif // !CMNBMPFORMAT_H__DATAPROCESSING__INCLUDED_
