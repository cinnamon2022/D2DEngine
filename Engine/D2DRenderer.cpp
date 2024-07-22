#include "pch.h"
#include "D2DRenderer.h"
#include "BitmapScene.h"

#pragma comment(lib, "d2d1.lib")
#pragma	comment(lib, "dwrite.lib")
#pragma	comment(lib, "windowscodecs.lib")
#pragma	comment(lib, "dxgi.lib")


D2DRenderer* D2DRenderer::Instance = nullptr;
D2D1_MATRIX_3X2_F D2DRenderer::m_CameraTransform = D2D1::IdentityMatrix();

D2DRenderer::D2DRenderer() : pRenderTarget(0), pHRenderTarget(0), _brushes(10, nullptr)
{
}

D2DRenderer::~D2DRenderer()
{

}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = pWICFactory->CreateDecoderFromFilename(
		szFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = pHRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
	}

	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	return hr;
}
D2D_SIZE_F D2DRenderer::GetScreenSize() const
{
	return m_ScreenSize;
}

void D2DRenderer::SetScreenSize(UINT Width, UINT Height)
{
	m_ScreenSize.width = Width;
	m_ScreenSize.height = Height;
}
BOOL D2DRenderer::InitDirect2D(HWND& hWnd)
{
	WCHAR buffer[MAX_PATH];
	// Get the current working directory
	DWORD result = GetCurrentDirectory(MAX_PATH, buffer);
	OutputDebugString(buffer);

	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
			이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
			DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
		*/
		//pD2DFactory = new ID2D1Factory();
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
		*/
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U m_ScreenSize = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		// Create a Direct2D render target.
		hr = pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, m_ScreenSize),
			&pHRenderTarget);

	}


	pHRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_brushes[0]);
	pHRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &_brushes[1]);

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pWICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"Cooper", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}

	//// VRAM 정보얻기 위한 개체 생성
	//if (SUCCEEDED(hr))
	//{
	//	// Create DXGI factory
	//	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
	//}
	//if (SUCCEEDED(hr))
	//{
	//	m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
	//}

	return true;
}

void D2DRenderer::UninitDirect2D()
{
	if (pWICFactory) pWICFactory->Release();
	if (pRenderTarget) pRenderTarget->Release();
	if (pHRenderTarget) pHRenderTarget->Release();
	if (pD2DFactory) pD2DFactory->Release();

	// COM 사용 끝
	//CoUninitialize();
}

size_t D2DRenderer::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	m_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}

D2DRenderer* D2DRenderer::Get()
{
	if (Instance == nullptr)
	{
		Instance = new D2DRenderer;
	}
	return Instance;
}


void D2DRenderer::WriteText(std::wstring text, const float _left, const float _top, const float _right, const float _bottom, const int _brushType)
{
	pHRenderTarget->DrawText(
		text.c_str(),
		text.size(),
		m_pDWriteTextFormat,
		D2D1::RectF(
			_left, _top,
			_right, _bottom
		),
		_brushes[_brushType]
	);
}

void D2DRenderer::DrawRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType)
{
	pHRenderTarget->DrawRectangle(
		D2D1::RectF(
			_left, _top,
			_right, _bottom
		),
		_brushes[_brushType]
	);
}
