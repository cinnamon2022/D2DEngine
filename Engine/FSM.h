#pragma once
#include "Component.h"

class FSMstate;

class FSM : public Component
{
public:
	FSM() = default;
	virtual ~FSM();

protected:
	FSMstate* m_pCurrState = nullptr;  // ���� ����	
	FSMstate* m_pNextState = nullptr;	// ���� ����

	std::map<std::string, FSMstate*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	virtual void Update(float DeltaTime);
	void SetNextState(std::string stateName);

	template<typename T>
	void CreateState(const std::string StateName)
	{
		T* pState = new T(this, StateName);
		m_pStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

