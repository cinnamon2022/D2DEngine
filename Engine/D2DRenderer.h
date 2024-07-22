#pragma once
class BitmapScene;
#define BLACK 0
#define GRAY 1
class D2DRenderer
{
private:
	static D2DRenderer* Instance;					// 싱글톤 인스턴스
public:
	ID2D1Factory* pD2DFactory;// D2D 개체 인터페이스 포인터 변수

	ID2D1RenderTarget* pRenderTarget;
	ID2D1HwndRenderTarget* pHRenderTarget;

	IWICImagingFactory* pWICFactory;

	D2D_SIZE_F				m_ScreenSize;

	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F m_CameraTransform;		// 카메라의 좌표계로 변환하는 카메라 월드의 역행렬

	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	D2D_SIZE_F GetScreenSize() const;
	void WriteText(std::wstring text, const float _left, const float _top, const float _right, const float _bottom, const int _brushType = 0);
	void DrawRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType = 0);
	void SetScreenSize(UINT Width, UINT Height);
	BOOL InitDirect2D(HWND& hWnd);
	void UninitDirect2D();

	IDWriteFactory* m_pDWriteFactory;	// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format
	std::vector<ID2D1SolidColorBrush*> _brushes;	// 렌더타겟이 생성하는 리소스 역시 장치의존
	IDXGIFactory4* m_pDXGIFactory;		// DXGI팩토리
	IDXGIAdapter3* m_pDXGIAdapter;		// 비디오카드 정보에 접근 가능한 인터페이스

	size_t GetUsedVRAM();

	static D2DRenderer* Get();
};

