#pragma once
/*
	���� ������Ʈ�� ����� ������Ʈ ������ �и��ϱ� ���� �߻� Ŭ����
	���ӿ�����Ʈ�� ������Ʈ�� �������� �̷������.
	������Ʈ�� ������ GameObject�� CreateComponent<T> �� ���� �̷������.
*/
class GameObject; 
class Component
{
public:
	Component();
	virtual ~Component();
	GameObject* m_pOwner = nullptr;

	GameObject* GetOwner() { return m_pOwner; }
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }


	virtual void Update() abstract;
	virtual void Render() abstract;
};

