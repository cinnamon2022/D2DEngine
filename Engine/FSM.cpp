#include "pch.h"
#include "FSM.h"
#include "FSMstate.h"



FSM::~FSM()
{
	for (auto& state : m_pStates)
	{
		delete state.second;
	}
	m_pStates.clear();
}

void FSM::Update(float DeltaTime)
{
	if (m_pCurrState != m_pNextState)
	{
		if (m_pCurrState != nullptr)
		{
			m_pCurrState->Exit();
		}
		m_pCurrState = m_pNextState;
		m_pCurrState->Enter();
	}
	else
	{
		m_pCurrState->Update(DeltaTime);
	}

}

void FSM::SetNextState(std::string stateName)
{
	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pNextState = it->second;
	}
}