#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"

// ����������
void TitleScene::Initialize()
{
	start_btn_collision = false;
	help_btn_collision = false;
	end_btn_collision = false;
	canClick = false;
	frame_count = 0;
}

// �X�V����
eSceneType TitleScene::Update()
{
	// �t���[���J�E���g��10�ȏ�ɂȂ�����N���b�N�ł���悤�ɂ���
	if (frame_count >= 10)
	{
		canClick = true;
	}
	else
	{
		frame_count++;
	}
	
	InputManager* input = InputManager::GetInstance();

    // �X�^�[�g�{�^���ƃv���C���[�J�[�\���̓����蔻��
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, START_BUTTON_LY, START_BUTTON_RY) == 1)
	{
		// �������Ă�����A�t���O��true�ɂ���
		start_btn_collision = true;
	}
	else
	{
		start_btn_collision = false;
	}

	// �w���v�{�^���ƃv���C���[�J�[�\���̓����蔻��
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, HELP_BUTTON_LY, HELP_BUTTON_RY) == 1)
	{
		// �������Ă�����A�t���O��true�ɂ���
		help_btn_collision = true;
	}
	else
	{
		help_btn_collision = false;
	}

	// �G���h�{�^���ƃv���C���[�J�[�\���̓����蔻��
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, END_BUTTON_LY, END_BUTTON_RY) == 1)
	{
		// �������Ă�����A�t���O��true�ɂ���
		end_btn_collision = true;
	}
	else
	{
		end_btn_collision = false;
	}

	// �{�^���̏�ŃN���b�N������A���ꂼ��̉�ʂɑJ�ڂ���
	if (canClick == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		if (start_btn_collision == true)
		{
			// �X�^�[�g�{�^�����Q�[�����C����ʂɑJ��
			return eSceneType::eGameMain;
		}
		else if (help_btn_collision == true)
		{
			// �w���v�{�^�����w���v��ʂɑJ��
			return eSceneType::eHelp;
		}
		else if (end_btn_collision == true)
		{
			// �G���h�{�^�����G���h��ʂɑJ��
			return eSceneType::eEnd;
		}
	}

	return GetNowSceneType();
}

// �`�揈��
void TitleScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, 1280, 720, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(90);
	DrawString(540, 80, "Title", 0xffffff);

	int button_color = 0xD6A15D;         // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff;  // �{�^���̕����̃J���[�R�[�h
	int button_string_spacing = 20;      // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	// ���j���[�{�^��
	// �X�^�[�g�{�^��
	if (start_btn_collision == true)
	{
		// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, START_BUTTON_LY, BUTTON_RX, START_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 90, START_BUTTON_LY + button_string_spacing, "�͂��߂�", button_string_color);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, START_BUTTON_LY, BUTTON_RX, START_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 90, START_BUTTON_LY + button_string_spacing, "�͂��߂�", button_string_color);
	}

	// �w���v�{�^��
	if (help_btn_collision == true)
	{
		// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, HELP_BUTTON_LY, BUTTON_RX, HELP_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 75, HELP_BUTTON_LY + button_string_spacing, "�����т���", button_string_color);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, HELP_BUTTON_LY, BUTTON_RX, HELP_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 75, HELP_BUTTON_LY + button_string_spacing, "�����т���", button_string_color);
	}

	// �G���h�{�^��
	if (end_btn_collision == true)
	{
		// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, END_BUTTON_LY, BUTTON_RX, END_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 105, END_BUTTON_LY + button_string_spacing, "�����", button_string_color);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, END_BUTTON_LY, BUTTON_RX, END_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 105, END_BUTTON_LY + button_string_spacing, "�����", button_string_color);

	}
}

	

// �I��������
void TitleScene::Finalize()
{
}

// ���݂̃V�[������Ԃ�
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}