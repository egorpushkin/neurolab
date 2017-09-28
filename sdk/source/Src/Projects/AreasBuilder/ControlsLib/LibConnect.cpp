#include "stdafx.h"
#include "LibConnect.h"

using namespace Gdiplus;

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