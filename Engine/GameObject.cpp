#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "D2DRenderer.h"

GameObject::GameObject()
{
	pObjAnimation = new AnimationScene;
}

GameObject::~GameObject()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		delete pComponent;
	}
	m_OwnedComponents.clear();
	delete pObjAnimation;
}

void GameObject::Update(float deltaTime)
{
	for (auto& pComponent : m_OwnedComponents) //게임오브젝트에 붙어있는 컴포넌트들을 돌아다니며 업데이트 해주기
	{
		pComponent->Update();
	}
	if (m_pRootScene)
		m_BoundBox.m_Center = m_pRootScene->GetWorldLocation();
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	D2D1_MATRIX_3X2_F Transform = pObjAnimation->m_WorldTransform * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);

	D2DRenderer::Get()->DrawRectangle(
		m_BoundBox.GetMinX(),
		m_BoundBox.GetMinY(),
		m_BoundBox.GetMaxX(),
		m_BoundBox.GetMaxY(), 1
	);
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Render();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	m_OwnedComponents.push_back(pComponent);
}

D2D1_VECTOR_2F GameObject::GetWorldLocation()
{
	D2D1_VECTOR_2F temp{ 0,0 };
	if (m_pRootScene)
		temp = m_pRootScene->GetWorldLocation();
	return temp;
}
