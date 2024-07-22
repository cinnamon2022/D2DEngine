#include "../Engine/pch.h"
#include "DemoApp.h"
#include "..//Engine/TimeManager.h"
#include "../Engine/D2DRenderer.h"

BOOL DemoApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);
	D2DRenderer::Get()->SetScreenSize(1024, 768);
	TimeManager::GetInstance()->Init();

	pWorld = new World;

	return 0;
}

void DemoApp::Update(float fTimeElapsed)
{
	TimeManager::GetInstance()->Update();
	pWorld->Update(fTimeElapsed);
}

void DemoApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	pWorld->Render(pRenderTarget);
	pRenderTarget->SetTransform(D2D1::IdentityMatrix());
	std::wstring text = L"존재하는 오브젝트 개수 : " + std::to_wstring(pWorld->m_GameObjects.size()) + L"\n" +
		L"그려지는 오브젝트 개수 : " + std::to_wstring(pWorld->renderCount);
	D2DRenderer::Get()->WriteText(text, 0, 0, 700, 100);

	D2DRenderer::Get()->WriteText(L"방향키로 카메라 이동, ENTER 캐릭터 소환, ESC 캐릭터 제거", 0, 800, 700, 600);

	pRenderTarget->EndDraw();
}

