#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"

World::World()
{
	// 화면크기 정보를 가져와서
	/*float width = D2DRenderer::Get()->GetScreenSize().width;
	float height = D2DRenderer::Get()->GetScreenSize().height;
	m_CullingBoundDefault.SetExtent(width / 2, height / 2);
	m_CullingBoundDefault.SetCenter(0, 0);
	SetCullingBound(&m_CullingBoundDefault);*/
	pCamera = new CameraScene;
}

World::~World()
{
	delete pCamera;
}

void World::Update(float deltaTime)
{
	pCamera->Update();

	if (GetAsyncKeyState(VK_RETURN))
	{
		int randX = rand() % 1920;
		int randY = rand() % 1080;
		GameObject* newObj = new GameObject;
		newObj->pObjAnimation->Load(L"Run.png");
		newObj->pObjAnimation->LoadAnimationAsset(L"Run");
		newObj->pObjAnimation->SetAnimation(1, 0);
		newObj->pObjAnimation->m_RelativeLocation = { (float)randX,(float)randY };
		m_GameObjects.push_back(newObj);
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		if (!m_GameObjects.empty()) {
			delete* m_GameObjects.begin();
			m_GameObjects.erase(m_GameObjects.begin());
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		pCamera->m_RelativeLocation.x -= 500 * deltaTime;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		pCamera->m_RelativeLocation.x += 500 * deltaTime;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		pCamera->m_RelativeLocation.y -= 500 * deltaTime;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		pCamera->m_RelativeLocation.y += 500 * deltaTime;
	}

	for (int i = 0; i < m_GameObjects.size(); i++) {
		if (!m_GameObjects.empty()) {
			float leftX = m_GameObjects[i]->pObjAnimation->m_DstRect.left;
			float rightX = m_GameObjects[i]->pObjAnimation->m_DstRect.right;
			float topY = m_GameObjects[i]->pObjAnimation->m_DstRect.top;
			float bottomY = m_GameObjects[i]->pObjAnimation->m_DstRect.bottom;
			float x = m_GameObjects[i]->pObjAnimation->GetWorldLocation().x;
			float y = m_GameObjects[i]->pObjAnimation->GetWorldLocation().y;

			m_GameObjects[i]->pObjAnimation->Update();
			m_GameObjects[i]->m_BoundBox.SetCenter(x + (rightX - leftX) / 2, y + (bottomY - topY) / 2);
			m_GameObjects[i]->m_BoundBox.SetExtent((rightX - leftX) / 2, (bottomY - topY) / 2);
		}
	}
	pCamera->Update();

	pCamera->m_ViewBoundBox.SetCenter(pCamera->GetWorldLocation().x + D2DRenderer::Get()->GetScreenSize().width / 2, pCamera->GetWorldLocation().y + D2DRenderer::Get()->GetScreenSize().height / 2);
	pCamera->m_ViewBoundBox.SetExtent(D2DRenderer::Get()->GetScreenSize().width / 2, D2DRenderer::Get()->GetScreenSize().height / 2);


	for (auto& obj : m_GameObjects)
	{
		obj->Update(deltaTime);
	}
}

void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	D2D1_MATRIX_3X2_F cameraTransformMatrix = pCamera->GetTransformMatrix();
	D2D1InvertMatrix(&cameraTransformMatrix);
	pRenderTarget->SetTransform(cameraTransformMatrix); //추가함.

	D2DRenderer::m_CameraTransform = cameraTransformMatrix;
	renderCount = 0;

	D2DRenderer::Get()->DrawRectangle(
		pCamera->m_ViewBoundBox.GetMinX(),
		pCamera->m_ViewBoundBox.GetMinY(),
		pCamera->m_ViewBoundBox.GetMaxX(),
		pCamera->m_ViewBoundBox.GetMaxY()
	);
	for (int i = 0; i < m_GameObjects.size(); i++) {
		if (m_GameObjects[i] != nullptr)
		{
			if (m_GameObjects[i]->m_BoundBox.CheckIntersect(pCamera->m_ViewBoundBox) == false) continue;
			pRenderTarget->SetTransform(m_GameObjects[i]->pObjAnimation->GetTransformMatrix() * cameraTransformMatrix);

			//m_GameObjects[i]->pObjAnimation->m_WorldTransform = m_GameObjects[i]->pObjAnimation->m_WorldTransform * cameraTransformMatrix;
			m_GameObjects[i]->pObjAnimation->Render();
			//m_GameObjects[i]->Render(pRenderTarget);	//박스그리는애

			renderCount++;
		}
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}
