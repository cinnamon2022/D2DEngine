#include "pch.h"
#include "InputManager.h"



void InputManager::Init(HWND hWnd)
{
	_hwnd = hWnd;
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (unsigned int key = 0; key < KEY_TYPE_COUNT; key++)
	{
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			if (state == KeyState::Pressed || state == KeyState::Down)
				state = KeyState::Pressed;
			else
				state = KeyState::Down;
		}
		else
		{
			KeyState& state = _states[key];
			if (state == KeyState::Pressed || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}
	::GetCursorPos(&_mousePos);				// �����쿡�� �������ִ� �⺻ �Լ�.
	::ScreenToClient(_hwnd, &_mousePos);	// �տ� :: ���ִ� ������ �����Լ����� ��������� �ϱ� ������.
}
