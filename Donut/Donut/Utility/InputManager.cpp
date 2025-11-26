#include "InputManager.h"
#include "DxLib.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance()
{
	// 初回呼び出しの際に新しいオブジェクトを生成
	if (instance == nullptr)
	{
		instance = new InputManager();
	}

	// 常にインスタンスを返す
	return instance;
}

void InputManager::DeleteInstance()
{
	// インスタンス削除
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputManager::Update()
{
	// キー入力値の更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// マウス入力値の更新
	old_mouse = now_mouse;

	// XInputコントローラーの入力値を取得する
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);

	// ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	// トリガー入力値の更新(0.0f～1.0fに範囲を制限する)
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	// 左スティック入力値の更新(-1.0f～1.0fに範囲を制限する)
	if (input_state.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = -((float)input_state.ThumbLY / (float)SHRT_MIN);
	}

	// 右スティック入力値の更新(-1.0f～1.0fに範囲を制限する)
	if (input_state.ThumbRX > 0.0f)
	{
		stick[1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state.ThumbRY > 0.0f)
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = -((float)input_state.ThumbRY / (float)SHRT_MIN);
	}
}

eInputState InputManager::GetKeyInputState(int keycode)
{
	if (CheckKeycodeRange(keycode))
	{
		if (old_key[keycode] == TRUE)
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::eHeld;
			}
			else
			{
				return eInputState::eRelease;
			}
		}
		else
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::ePress;
			}
			else
			{
				return eInputState::eNone;
			}
		}
	}

	return eInputState::eNone;
}

eInputState InputManager::GetMouseInputState(int mouse_button)
{
	//マウスの左ボタンが押されているかチェック
	if ((GetMouseInput() & mouse_button) != 0)
	{
		//押されてる
		now_mouse = 1;
	}
	else
	{
		//押されていない
		now_mouse = 0;
	}

	if (now_mouse == 1 && old_mouse == 0)
	{//クリックした瞬間を取る
		return eInputState::ePress;
	}
	else if (now_mouse == 1 && old_mouse == 1)
	{//ずっと押し続けているか
		return eInputState::eHeld;
	}
	else if (now_mouse == 0 && old_mouse == 1)
	{//放した瞬間
		return eInputState::eRelease;
	}

	return eInputState::eNone;
}

Vector2D InputManager::GetMouseLocation()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse_location.x = (float)x;
	mouse_location.y = (float)y;

	return mouse_location;
}

int InputManager::GetMouseWheelRotaVolume()
{
	// 前回 GetMouseWheelRotVol が呼ばれてから今回までの回転量を足す
	wheel += GetMouseWheelRotVol();

	return wheel;
}

bool InputManager::IsMouseTriggered()
{
	bool mouseNow = (GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress);
	bool triggered = (mouseNow && !mouse_prev);
	mouse_prev = mouseNow;
	return triggered;
}

bool InputManager::GetButton(int button)
{
	return CheckButtonRange(button) && (now_button[button] && old_button[button]);
}

bool InputManager::GetButtonDown(int button)
{
	return CheckButtonRange(button) && (now_button[button] && !old_button[button]);
}

bool InputManager::GetButtonUp(int button)
{
	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
}

float InputManager::GetLeftTrigger()
{
	return trigger[0];
}

float InputManager::GetRightTrigger()
{
	return trigger[1];
}

Vector2D InputManager::GetLeftStick()
{
	return stick[0];
}

Vector2D InputManager::GetRightStick()
{
	return stick[1];
}

bool InputManager::CheckKeycodeRange(int keycode)
{
	return (0 <= keycode && keycode < D_KEYCODE_MAX);
}

bool InputManager::CheckButtonRange(int button)
{
	return (0 <= button && button < 16);
}
