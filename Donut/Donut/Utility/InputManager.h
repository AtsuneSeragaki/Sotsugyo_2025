#pragma once

#include "Vector2D.h"

#define   D_KEYCODE_MAX  (256)

enum class eInputState : unsigned char
{
	eNone,
	ePress,
	eRelease,
	eHeld,
};

// Singleton:�N���X��1�̃C���X�^���X�݂̂�ۏ؂��違���̃C���X�^���X�ւ̑��A�N�Z�X�E�|�C���g��񋟂���
class InputManager
{
private:
	static InputManager* instance;

	char now_key[D_KEYCODE_MAX] = {};  // ���݂̃t���[�����͒l
	char old_key[D_KEYCODE_MAX] = {};  // �ߋ��̃t���[�����͒l

	int now_mouse;                 // ���݂̃t���[�����͒l
	int old_mouse;                 // �ߋ��̃t���[�����͒l
	Vector2D mouse_location;       // �}�E�X���W
	int wheel;                     // �}�E�X�̃z�C�[����]��

	bool now_button[16];        // ���݂̃t���[�����͒l
	bool old_button[16]; // �ߋ��̃t���[�����͒l
	float trigger[2];    // ���E�g���K�[�̓��͒l
	Vector2D stick[2];   // ���E�X�e�B�b�N�̓��͒l

private:
	// �R���X�g���N�^��private�ɂ���
	InputManager() = default;
	// �R�s�[�K�[�h�̍쐬
	// �R�s�[�R���X�g���N�^�֎~
	InputManager(const InputManager&) = delete;
	// ������Z�q�֎~
	InputManager& operator = (const InputManager&) = delete;

public:
	~InputManager() = default;

public:
	// �R���X�g���N�^�ƃf�X�g���N�^�Ƃ��ċ@�\����ÓI�����o�֐����쐬����
	// ����Ăяo���̍ۂɐV�����I�u�W�F�N�g�𐶐����A�֐��͏�ɂ��̃C���X�^���X��Ԃ��悤�ɂ���
	static InputManager* GetInstance();
	static void DeleteInstance();

public:
	// �X�V����
	void Update();

public:
	// ����(keycode)�L�[�̏�Ԃ��擾���ĕԂ�
	eInputState GetKeyInputState(int keycode);

	// �}�E�X�̓��͎擾����
	eInputState GetMouseInputState(int mouse_button);
	// �}�E�X�̍��W�擾����
	Vector2D GetMouseLocation();
	// �}�E�X�̃z�C�[����]�ʎ擾����
	int GetMouseWheelRotaVolume();

	// �{�^���̓��͎擾����
	bool GetButton(int button);     // ���������Ă����
	bool GetButtonDown(int button); // �������u��
	bool GetButtonUp(int button);   // �������u��

	// �g���K�[���͎擾����
	float GetLeftTrigger();  // ���g���K�[
	float GetRightTrigger(); // �E�g���K�[

	// �X�e�B�b�N���͎擾����
	Vector2D GetLeftStick();  // ���X�e�B�b�N
	Vector2D GetRightStick(); // �E�X�e�B�b�N

private:
	// �L�[�z��͈̓`�F�b�N
	bool CheckKeycodeRange(int keycode);

	// �{�^���z��͈̓`�F�b�N
	bool CheckButtonRange(int button);
};

// �ÓI�����o�֐��̒��ł́A�ÓI�����o�ϐ������ĂׂȂ�
// ���ʂ̃����o�֐��̒��ŁA�ÓI�����o���ĂԂ̂�OK