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

	// �{�^���ƃv���C���[�J�[�\���̓����蔻��
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
	DrawString(500, 35, "Result", 0xffffff);

	DrawBox(340, 150, 940, 560, 0xffffff, TRUE);

	// �X�R�A
	SetFontSize(40);
	DrawFormatString(540, 170, 0x000000, "Your score");
	SetFontSize(70);
	DrawFormatString(502, 230, 0x000000, "%08d", score);

	// �����L���O�\��
	SetFontSize(40);
	DrawFormatString(580, 320, 0x000000, "Ranking");
	SetFontSize(40);
	DrawFormatString(520, 380, 0x000000, "No.1:%08d", score);
	DrawFormatString(520, 440, 0x000000, "No.2:%08d", score);
	DrawFormatString(520, 500, 0x000000, "No.3:%08d", score);


	int button_color = 0xD6A15D;        // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff; // �{�^���̕����̃J���[�R�[�h
	int button_string_yspacing = 20;    // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	int restart_button_xspacing = 55;   // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)
	int title_button_xspacing = 45;     // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)

	// ���j���[�{�^��
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (button[i].collision == true)
		{
			// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
			SetDrawBright(128, 128, 128);
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);
			SetDrawBright(255, 255, 255);

			// ���\���p����(�摜���o���������)
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "������x�V��", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "�^�C�g���ɖ߂�", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			
		}
		else
		{
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);

			// ���\���p����(�摜���o���������)
			if (i == 0)
			{
				SetFontSize(30);
				DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "������x�V��", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "�^�C�g���ɖ߂�", button_string_color);
			}
		}
	}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
