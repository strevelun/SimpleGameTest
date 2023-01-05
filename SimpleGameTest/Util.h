#pragma once
#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib")

extern ID2D1HwndRenderTarget* g_pRenderTarget;
extern IWICImagingFactory* g_pWICFactory;

extern HRESULT LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _pBitmap);