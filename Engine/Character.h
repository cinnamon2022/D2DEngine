#pragma once
#include "GameObject.h"

class AnimationScene;
class AABB;
class Character : public GameObject
{
public:
	Character();
	virtual ~Character();

	AABB* m_pAABB = nullptr;
	AnimationScene* m_pAnimationScene = nullptr;
	//CollisionBox* m_pCollisionBox = nullptr;
};
