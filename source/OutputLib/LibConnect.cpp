#include "stdafx.h"
#include "LibConnect.h"

GdiplusStartupInput			gdiplusStartupInput;
ULONG_PTR					gdiplusToken;

void InitializeGDIP()
{
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void ReleaseGDIP()
{
	GdiplusShutdown(gdiplusToken);
}