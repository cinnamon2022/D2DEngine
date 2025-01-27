#pragma once
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

class CameraScene : public Scene
{
public:
	CameraScene();
	virtual ~CameraScene();

	AABB m_ViewBoundBox;
	virtual void Update();
};

