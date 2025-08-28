#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

ResultScene::ResultScene(int score)
{
	this->score = score;
	frame_count = 0;
	can_click = false;

	// ���X�^�[�g�{�^��������
	button[0] = { RESTART_BUTTON_LX,RESTART_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eGameMain };

	// �^�C�g���{�^��������
	button[1] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eTitle };
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update()
{
	// �t���[���J�E���g��10�ȏ�ɂȂ�����N���b�N�ł���悤�ɂ���
	if (frame_count >= 10)
	{
		can_click = true;
	}
	else
	{
		frame_count++;
	}

	InputManager* input = InputManager::GetInstance();

	// ���X�^�[�g�{�^���ƃv���C���[�J�[�\���̓����蔻��

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (CheckPlayerButtonCollision(button[i].lx, button[i].rx, button[i].ly, button[i].ry) == 1)
		{
			button[i].collision = true;
		}
		else
		{
			button[i].collision = false;
		}
	}

	// �{�^���̏�ŃN���b�N������A���ꂼ��̉�ʂɑJ�ڂ���
	if (can_click == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		for (int i = 0; i < BUTTON_NUM; i++)
		{
			if (button[i].collision == true)
			{
				// ���ꂼ��̉�ʂɑJ��
				return button[i].targetScene;
			}
		}
	}

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, 1280, 720, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(90);
	DrawString(540, 80, "Result", 0xffffff);

	// �X�R�A
	SetFontSize(30);
	DrawFormatString(540, 150, 0xffffff, "�X�R�A�F%d", score);

	int button_color = 0xD6A15D;        // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff; // �{�^���̕����̃J���[�R�[�h
	int button_string_yspacing = 20;    // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	int restart_button_xspacing = 55;   // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)
	int title_button_xspacing = 45;     // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)

	// ���j���[�{�^��
	// ���X�^�[�g�{�^��

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (button[i].collision == true)
		{
			// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
			SetDrawBright(128, 128, 128);
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);
			SetFontSize(30);
			DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "������x�V��", button_string_color);
			SetDrawBright(255, 255, 255);
		}
		else
		{

		}
	}

	//if (restart_btn_collision == true)
	//{
	//	// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
	//	SetDrawBright(128, 128, 128);
	//	DrawBox(RESTART_BUTTON_LX, BUTTON_LY, RESTART_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(RESTART_BUTTON_LX + restart_button_xspacing, BUTTON_LY + button_string_yspacing, "������x�V��", button_string_color);
	//	SetDrawBright(255, 255, 255);
	//}
	//else
	//{
	//	DrawBox(RESTART_BUTTON_LX, BUTTON_LY, RESTART_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(RESTART_BUTTON_LX + restart_button_xspacing,BUTTON_LY + button_string_yspacing, "������x�V��", button_string_color);
	//}

	//// �^�C�g���{�^��
	//if (title_btn_collision == true)
	//{
	//	// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
	//	SetDrawBright(128, 128, 128);
	//	DrawBox(TITLE_BUTTON_LX, BUTTON_LY, TITLE_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(TITLE_BUTTON_LX + title_button_xspacing, BUTTON_LY + button_string_yspacing, "�^�C�g���ɖ߂�", button_string_color);
	//	SetDrawBright(255, 255, 255);
	//}
	//else
	//{
	//	DrawBox(TITLE_BUTTON_LX, BUTTON_LY, TITLE_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(TITLE_BUTTON_LX + title_button_xspacing, BUTTON_LY + button_string_yspacing, "�^�C�g���ɖ߂�", button_string_color);
	//}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
