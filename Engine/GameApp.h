#pragma once
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
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
	WCHAR           szTitle[MAX_LOADSTRING] = L"title";                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
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

