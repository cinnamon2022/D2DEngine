#pragma once
enum class KeyType
{
	W = 'W',
	S = 'S',
	A = 'A',
	D = 'D',
	Right = VK_RIGHT,
	Left = VK_LEFT,
	Space = VK_SPACE,
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,
	ESC = VK_ESCAPE,
};

enum class KeyState
{
	None,
	Pressed,
	Down,
	Up,
	End
};

const int KEY_TYPE_COUNT = static_cast<int>(256) + 1;
const int KEY_STATE_COUNT = static_cast<int>(KeyState::End);

class InputManager
{
private:
	InputManager() = default;

public:
	static InputManager* GetInstance()
	{
		static InputManager _instance;
		return &_instance;
	}
public:
	void Init(HWND hwnd);
	void Update();

	bool GetButtonPressed(KeyType type) { return GetState(type) == KeyState::Pressed; }
	bool GetButtonDown(KeyType type) { return GetState(type) == KeyState::Down; }

	bool GetButtonUp(KeyType type) { return GetState(type) == KeyState::Up; }
	Vector2D GetMousePos() { return  {(float)_mousePos.x, (float)_mousePos.y };
}

private:
	KeyState GetState(KeyType key) { return _states[static_cast<unsigned char>(key)]; }
private:
	HWND _hwnd = 0;
	KeyState _states[KEY_TYPE_COUNT];
	POINT _mousePos{};

};

