#pragma once
#include "Component.h"
class Scene : public Component
{
public:
	Scene();
	virtual ~Scene();

	Scene* m_pParentScene = nullptr;// �θ� Scene ������Ʈ
	D2D_VECTOR_2F		m_RelativeCenter = { 0,0 };
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };		// ��� ũ��
	float				m_RelativeRotation = 0;			// ��� ȸ��
	D2D_VECTOR_2F		m_RelativeLocation = { 0,0 };	// ��� ��ġ
	D2D_MATRIX_3X2_F	m_RelativeTransform;			// ��� ���� ��ȯ
	D2D_MATRIX_3X2_F	m_WorldTransform;				// �θ���� �ݿ��� ���� ��ȯ

	// m_RelativeTransform ��  m_WorldTransform �� ����Ѵ�.
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