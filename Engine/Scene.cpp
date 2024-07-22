#include "pch.h"
#include "Scene.h"
#include "D2DRenderer.h"

Scene::Scene()
{
	m_RelativeTransform = m_WorldTransform = D2D1::Matrix3x2F::Identity();
}

Scene::~Scene()
{
}

void Scene::UpdateTransform()
{
	m_RelativeTransform =
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}

void Scene::SetParent(Scene* pParentScene)
{
	m_pParentScene = pParentScene;
}

void Scene::Init()
{
}

void Scene::Update()
{
	UpdateTransform();
}

void Scene::Render()
{
#if _DEBUG	
	D2DRenderer::Get()->pRenderTarget->SetTransform(m_WorldTransform);

#endif // _DEBUG
}
