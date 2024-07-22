#include "pch.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	float width = 1024;
	float height = 768;

	m_ViewBoundBox.SetExtent(width / 2, height / 2);
}

CameraScene::~CameraScene()
{
}

void CameraScene::Update()
{
	Scene::UpdateTransform();
	m_ViewBoundBox.m_Center = GetWorldLocation();
}
