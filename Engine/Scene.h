#pragma once
#include "Component.h"
class Scene : public Component
{
public:
	Scene();
	virtual ~Scene();

	Scene* m_pParentScene = nullptr;// 부모 Scene 컴포넌트
	D2D_VECTOR_2F		m_RelativeCenter = { 0,0 };
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };		// 상대 크기
	float				m_RelativeRotation = 0;			// 상대 회전
	D2D_VECTOR_2F		m_RelativeLocation = { 0,0 };	// 상대 위치
	D2D_MATRIX_3X2_F	m_RelativeTransform;			// 상대 복합 변환
	D2D_MATRIX_3X2_F	m_WorldTransform;				// 부모까지 반영된 최종 변환

	// m_RelativeTransform 과  m_WorldTransform 을 계산한다.
	void UpdateTransform();
	void SetParent(Scene* pParentScene);

	D2D1_MATRIX_3X2_F GetTransformMatrix()
	{
		return m_WorldTransform;
	}
	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;		//???dummystructname??? 
		out.y = m_WorldTransform._32;
		return out;
	}
	virtual void Init();
	virtual void Update();
	virtual void Render();
};