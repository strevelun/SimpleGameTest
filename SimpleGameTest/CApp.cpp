#include "CApp.h"
#include "Game.h"
#include "ResourceManager.h"
#include "CCore.h"

#include <windowsx.h>

CApp* CApp::m_inst = nullptr;


/*
HRESULT LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _pBitmap)
{
	
	char dest[100];
	sprintf(dest, "%s%s", _path, _wcFileName);
	wchar_t wtext[20];
	mbstowcs(wtext, dest, strlen(dest) + 1);//Plus null
	LPWSTR ptr = wtext;
	

	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	hr = g_pWICFactory->CreateDecoderFromFilename(L"Resource\\Image\\Tile\\NonWalkable\\Object2_2.png", NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr)) return hr;

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr)) return hr;

	IWICFormatConverter* pConverter = nullptr;
	hr = g_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return hr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return hr;

	hr = g_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, _pBitmap);
	if (FAILED(hr)) return hr;


	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return hr;
}
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return CApp::GetInstance()->Proc(hWnd, message, wParam, lParam);
}

HRESULT CApp::Init(HINSTANCE hInstance, int nCmdShow)
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

	m_hInst = hInstance;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindow(L"D2DTutWindowClass", L"D2D1 Tutorial 1 : simple app",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!m_hWnd) return E_FAIL;

	ShowWindow(m_hWnd, nCmdShow);

	CCore::GetInst()->Init(m_hWnd);

	if (!ResourceManager::GetInst()->Init())
		return 0;

	return S_OK;
}


void CApp::Input()
{
	CScene::GetInst()->Input();
}

void CApp::Update()
{
	CScene::GetInst()->Update(m_mag);
}

void CApp::Render()
{
	CCore::GetInst()->Render(m_mag);
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

	CCore::GetInst()->CleanupDevice();
	CCore::DeleteInst();
	ResourceManager::DeleteInst();

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

	case WM_MOUSEMOVE:
		m_mouseX = GET_X_LPARAM(lParam);
		m_mouseY = GET_Y_LPARAM(lParam);
		break;

	case WM_LBUTTONDOWN:
		CScene::GetInst()->SetTile(m_mouseX / m_mag, m_mouseY / m_mag, ObjType::Walkable);
		break;

	case WM_RBUTTONDOWN:
		CScene::GetInst()->SetTile(m_mouseX / m_mag, m_mouseY / m_mag, ObjType::None);
		break;

	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) < 0)
		{
			if (m_mag > MAG_MIN)
				m_mag -= MAG;
		}
		else
		{
			if (m_mag < MAG_MAX)
				m_mag += MAG;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
