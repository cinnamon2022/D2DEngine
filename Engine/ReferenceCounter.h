#pragma once
/*
	이 프로젝트의 Factory -> Product(Resource) 개념에서
	하나의 리소스를 참조하는 횟수를 추적하여 그 리소스를 참조하는것이 없을때,
	if (m_RefCount == 0) 일때, 해제 하기위한 시스템
*/
class ReferenceCounter
{
	unsigned int m_RefCount;
public:
	ReferenceCounter() :m_RefCount(0) {}
	//virtual 키워드 사용으로 파괴자를 가상함수로 만들어 delete를 호출할때 
	//파괴자호출이 자식의 파괴자 -> 부모의 파괴자 순으로 호출되도록한다. 
	//자식클래스에서 제거한 상태로 재정의 해도 virtual상태를 유지한다.

	virtual ~ReferenceCounter() {}
	unsigned int AddRef()
	{
		m_RefCount++;
		return m_RefCount;
	}
	unsigned int Release()
	{
		m_RefCount--;
		if (m_RefCount == 0)
		{	// 파괴자에 virtual 키워드를 사용했으므로 자식클래스의 파괴자가 호출된다. 	
			delete this;
			return 0;
		}
		return m_RefCount;
	}
	unsigned int GetRefCount()
	{
		return m_RefCount;
	}
};

