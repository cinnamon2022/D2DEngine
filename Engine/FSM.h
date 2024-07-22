#pragma once
#include "Component.h"

class FSMstate;

class FSM : public Component
{
public:
	FSM() = default;
	virtual ~FSM();

protected:
	FSMstate* m_pCurrState = nullptr;  // 현재 상태	
	FSMstate* m_pNextState = nullptr;	// 다음 상태

	std::map<std::string, FSMstate*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너

	virtual void Update(float DeltaTime);
	void SetNextState(std::string stateName);

	template<typename T>
	void CreateState(const std::string StateName)
	{
		T* pState = new T(this, StateName);
		m_pStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

