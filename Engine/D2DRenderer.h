#pragma once
class BitmapScene;
#define BLACK 0
#define GRAY 1
class D2DRenderer
{
private:
	static D2DRenderer* Instance;					// �̱��� �ν��Ͻ�
public:
	ID2D1Factory* pD2DFactory;// D2D ��ü �������̽� ������ ����

	ID2D1RenderTarget* pRenderTarget;
	ID2D1HwndRenderTarget* pHRenderTarget;

	IWICImagingFactory* pWICFactory;

	D2D_SIZE_F				m_ScreenSize;

	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F m_CameraTransform;		// ī�޶��� ��ǥ��� ��ȯ�ϴ� ī�޶� ������ �����

	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	D2D_SIZE_F GetScreenSize() const;
	void WriteText(std::wstring text, const float _left, const float _top, const float _right, const float _bottom, const int _brushType = 0);
	void DrawRectangle(const float _left, const float _top, const float _right, const float _bottom, const int _brushType = 0);
	void SetScreenSize(UINT Width, UINT Height);
	BOOL InitDirect2D(HWND& hWnd);
	void UninitDirect2D();

	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	std::vector<ID2D1SolidColorBrush*> _brushes;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����
	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;		// ����ī�� ������ ���� ������ �������̽�

	size_t GetUsedVRAM();

	static D2DRenderer* Get();
};

