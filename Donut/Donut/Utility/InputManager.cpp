#include "InputManager.h"
#include "DxLib.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance()
{
	// ����Ăяo���̍ۂɐV�����I�u�W�F�N�g�𐶐�
	if (instance == nullptr)
	{
		instance = new InputManager();
	}

	// ��ɃC���X�^���X��Ԃ�
	return instance;
}

void InputManager::DeleteInstance()
{
	// �C���X�^���X�폜
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputManager::Update()
{
	// �L�[���͒l�̍X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// �}�E�X���͒l�̍X�V
	old_mouse = now_mouse;

	// XInput�R���g���[���[�̓��͒l���擾����
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);

	// �{�^�����͒l�̍X�V
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	// �g���K�[���͒l�̍X�V(0.0f�`1.0f�ɔ͈͂𐧌�����)
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	// ���X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)
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

	// �E�X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)
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
	//�}�E�X�̍��{�^����������Ă��邩�`�F�b�N
	if ((GetMouseInput() & mouse_button) != 0)
	{
		//������Ă�
		now_mouse = 1;
	}
	else
	{
		//������Ă��Ȃ�
		now_mouse = 0;
	}

	if (now_mouse == 1 && old_mouse == 0)
	{//�N���b�N�����u�Ԃ����
		return eInputState::ePress;
	}
	else if (now_mouse == 1 && old_mouse == 1)
	{//�����Ɖ��������Ă��邩
		return eInputState::eHeld;
	}
	else if (now_mouse == 0 && old_mouse == 1)
	{//�������u��
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
	// �O�� GetMouseWheelRotVol ���Ă΂�Ă��獡��܂ł̉�]�ʂ𑫂�
	wheel += GetMouseWheelRotVol();

	return wheel;
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
