#pragma once
#include"../Engine/pch.h"
#include "../Engine/GameApp.h"
#include "../Engine/BitmapScene.h"
#include "../Engine/AnimationScene.h"
#include "../Engine/World.h"

class DemoApp : public GameApp
{
public:
	DemoApp() {}
	virtual ~DemoApp() {}


	virtual BOOL Initialize(HINSTANCE hInstance, int nCmdShow);

	virtual void Update(float fTimeElapsed) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

	World* pWorld = nullptr;

};

