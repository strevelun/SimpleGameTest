#pragma once
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

#define MAX_LOADSTRING 100
#define WIDTH           1200
#define HEIGHT          880

class CApp
{
private:
	static CApp* m_inst;

	WCHAR szTitle[MAX_LOADSTRING] = {};
	WCHAR szWindowClass[MAX_LOADSTRING] = {};

	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;

	ID2D1Factory* g_pD2DFactory = nullptr;
	ID2D1HwndRenderTarget* g_pRenderTarget = nullptr; 
	IDWriteFactory* g_pDWriteFactory = nullptr;
	IDWriteTextFormat* g_pDWTextFormat = nullptr;
	IWICImagingFactory* g_pWICFactory = nullptr;
	ID2D1SolidColorBrush* g_pBlackBrush = nullptr;

private:
	int m_screenWidth = 0;
	int m_screenHeight = 0;

private:
	CApp() { }
	~CApp() {}

private:
	HRESULT InitDevice();
	void CleanupDevice();
	HRESULT LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _ppBitmap);

public:
	static CApp* GetInstance()
	{
		if (m_inst == nullptr)  m_inst = new CApp();
		return m_inst;
	}

	HRESULT Init(HINSTANCE hInstance, int nCmdShow, int screenWidth, int screenHeight);
	void Input();
	void Update();
	void Render();
	int Run();

	LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};