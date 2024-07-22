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
	::GetCursorPos(&_mousePos);				// 윈도우에서 제공해주는 기본 함수.
	::ScreenToClient(_hwnd, &_mousePos);	// 앞에 :: 해주는 이유는 전역함수임을 명시적으로 하기 위함임.
}
