#include "CApp.h"

CApp* CApp::m_inst = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return CApp::GetInstance()->Proc(hWnd, message, wParam, lParam);
}

HRESULT CApp::InitDevice()
{
	HRESULT hr = S_OK;

	RECT	rc;
	GetClientRect(m_hWnd, &rc);

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	if (FAILED(hr)) return hr;

	hr = g_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&g_pRenderTarget);
	if (FAILED(hr)) return hr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pWICFactory));
	if (FAILED(hr)) return hr;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&g_pDWriteFactory));
	if (FAILED(hr)) return hr;

	static const WCHAR fontName[] = L"Gabriola";
	const FLOAT fontSize = 50.0f;

	hr = g_pDWriteFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		fontSize, L"en-us", &g_pDWTextFormat);
	if (FAILED(hr)) return hr;

	hr = g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_pBlackBrush);

	return hr;
}

void CApp::CleanupDevice()
{
	if (g_pWICFactory) g_pWICFactory->Release();
	if (g_pRenderTarget) g_pRenderTarget->Release();
	if (g_pD2DFactory) g_pD2DFactory->Release();
	CoUninitialize();
}

HRESULT CApp::LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _ppBitmap)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	hr = g_pWICFactory->CreateDecoderFromFilename(_wcFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr)) return hr;

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr)) return hr;

	IWICFormatConverter* pConverter = nullptr;
	hr = g_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return hr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return hr;

	hr = g_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, _ppBitmap);
	if (FAILED(hr)) return hr;


	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return hr;
}

HRESULT CApp::Init(HINSTANCE hInstance, int nCmdShow, int screenWidth, int screenHeight)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"D2DTutWindowClass";
	wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_hInst = hInstance;
	RECT rc = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindow(L"D2DTutWindowClass", L"D2D1 Tutorial 1 : simple app",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!m_hWnd) return E_FAIL;

	ShowWindow(m_hWnd, nCmdShow);

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	return S_OK;
}


void CApp::Input()
{
}

void CApp::Update()
{
}

void CApp::Render()
{
	g_pRenderTarget->BeginDraw();
	g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Aqua));

	D2D1_SIZE_F rtSize = g_pRenderTarget->GetSize();



	WCHAR wcText[] = L"1.23 fps";
	g_pRenderTarget->DrawTextW(wcText, ARRAYSIZE(wcText) - 1, g_pDWTextFormat, D2D1::RectF(0, 0, rtSize.width, rtSize.height), g_pBlackBrush);

	g_pRenderTarget->EndDraw();
}

int CApp::Run()
{
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Input();
			Update();
			Render();
		}
	}

	CleanupDevice();

    return (int)msg.wParam;
}

LRESULT CApp::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}