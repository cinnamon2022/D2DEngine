#pragma once
#include "CameraScene.h"
#include "GameObject.h"
#include "AABB.h"
// ������ ���踦 ��Ÿ���� Ŭ����
// GameObectŸ������ ������ ��ü���� �����Ͽ� Update, Render�� ȣ���Ѵ�.
class World
{
public:
	World();
	virtual ~World();

	int renderCount = 0;

	std::vector<GameObject*> m_GameObjects;
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

	CameraScene* pCamera = nullptr;

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }

	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);		// GameObject�� ��ӹ��� Ŭ������ ������ �� �ִ�.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};

