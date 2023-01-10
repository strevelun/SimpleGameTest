#include "CCore.h"
#include "CScene.h"

CCore* CCore::m_inst = nullptr;

CCore::CCore()
{
}

CCore::~CCore()
{

}

HRESULT CCore::InitDevice(HWND hWnd)
{
	HRESULT hr = S_OK;

	RECT	rc;
	GetClientRect(hWnd, &rc);

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (FAILED(hr)) return hr;

	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&m_pRenderTarget);
	if (FAILED(hr)) return hr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr)) return hr;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	if (FAILED(hr)) return hr;

	static const WCHAR fontName[] = L"Gabriola";
	const FLOAT fontSize = 50.0f;

	hr = m_pDWriteFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		fontSize, L"en-us", &m_pDWTextFormat);
	if (FAILED(hr)) return hr;

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);

	return hr;
}

HRESULT CCore::LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _pBitmap)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	hr = m_pWICFactory->CreateDecoderFromFilename(_wcFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr)) return hr;

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr)) return hr;

	IWICFormatConverter* pConverter = nullptr;
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return hr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return hr;

	hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, _pBitmap);
	if (FAILED(hr)) return hr;


	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return hr;
}


void CCore::CleanupDevice()
{
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pD2DFactory) m_pD2DFactory->Release();
	if (m_pWICFactory) m_pWICFactory->Release();
	CoUninitialize();
}

bool CCore::Init(HWND hWnd)
{
	if (FAILED(InitDevice(hWnd)))
	{
		CleanupDevice();
		return false;
	}
}

void CCore::Render(int _mag)
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Aqua));
	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();


	CScene::GetInst()->Render(m_pRenderTarget, m_pBlackBrush, _mag);
	m_pRenderTarget->EndDraw();
}