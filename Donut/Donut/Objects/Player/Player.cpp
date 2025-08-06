#include "Player.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

// �R���X�g���N�^
Player::Player() : is_click(false)
{
	// �ŏ���1�̃h�[�i�c��ݒ�
	donut_type = DonutType::DONUT_MINI_BASIC;
	r = 10.0f;
	donut_number = 1;

	// ���̃h�[�i�c��3�̃h�[�i�c��ݒ�
	next_donut_type = DonutType::DONUT_FRENCH_CRULLER;
	next_r = 30.0f;
	next_donut_number = 3;
}

// �f�X�g���N�^
Player::~Player()
{
}

// ����������
void Player::Initialize()
{
	
}

// �X�V����
void Player::Update()
{
	InputManager* input = InputManager::GetInstance();

	// �}�E�X��X���W���擾
	location.x = input->GetMouseLocation().x;

	// �J�[�\���ړ�����
	LocXControl();
}

// �`�揈��
void Player::Draw() const
{
	// �h�[�i�c���\��
	DrawCircleAA(location.x, location.y, r, 32, 0xffff00, TRUE);
	// �h�[�i�c�ԍ���\��
	DrawFormatString((int)location.x, (int)location.y - 3, 0x000000, "%d", donut_number);

	// ���ɗ��Ƃ��h�[�i�c��\��(�E��)
	DrawCircleAA(1000.0f, 60.0f, next_r, 32, 0xffff00, TRUE);
	// ���ɗ��Ƃ��h�[�i�c�ԍ���\��
	DrawFormatString((int)1000.0f, (int)60.0f - 3, 0x000000, "%d", next_donut_number);
}

// �I��������
void Player::Finalize()
{
}

// �h�[�i�c�������_���ɑI��
void Player::ChooseRandomDonut()
{
	// ���ɗ��Ƃ��h�[�i�c�������Ƃ��h�[�i�c�ɏ㏑��
	donut_type = next_donut_type;

	// ���ɗ��Ƃ��h�[�i�c�����߂Ȃ���
	next_donut_type = static_cast<DonutType>(rand() % (static_cast<int>(DonutType::DONUT_OLD_FASHIONED) + 1));
}

// �h�[�i�c�𗎂Ƃ��g�͈̔͂����ړ��o���Ȃ��悤�ɂ��鏈��
void Player::LocXControl()
{
	if (location.x > 880.0f - r)
	{// �E��
		location.x = 880.0f - r;
	}
	else if (location.x < 400.0f + r)
	{// ����
		location.x = 400.0f + r;
	}
}