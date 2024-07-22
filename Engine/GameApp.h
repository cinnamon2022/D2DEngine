#pragma once
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "resource.h"
#include <Windows.h>
#include "D2DRenderer.h"

class ResourceManager;
class D2DRenderer;
class World;

class GameApp
{
public:
	HINSTANCE       hInst;
	HWND            hWnd;

	HRESULT hr;

	RECT rc;
	WCHAR           szTitle[MAX_LOADSTRING] = L"title";                  // 제목 표시줄 텍스트입니다.
	WCHAR           szWindowClass[MAX_LOADSTRING] = L"hello";

	D2DRenderer* m_pRenderer = nullptr;
	ResourceManager* m_pResourceManager = nullptr;
	World* m_pWorld = nullptr;


	GameApp() {}
	virtual ~GameApp() {}
	virtual BOOL Initialize(HINSTANCE hInstance, int nCmdShow);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	void Uninitialize();
	ATOM MyRegisterClass(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Run(MSG& msg);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
	virtual void Update(float fTimeElapsed);
};

