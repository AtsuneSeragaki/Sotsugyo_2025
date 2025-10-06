#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

// ����������
void TitleScene::Initialize()
{
	can_click = false;
	frame_count = 0;

	button[0] = { BUTTON_LX, BUTTON_RX, START_BUTTON_LY, START_BUTTON_RY, false, eSceneType::eGameMain };
	button[1] = { BUTTON_LX,BUTTON_RX,HELP_BUTTON_LY,HELP_BUTTON_RY,false,eSceneType::eHelp };
	button[2] = { BUTTON_LX,BUTTON_RX,RANKING_BUTTON_LY,RANKING_BUTTON_RY,false,eSceneType::eRanking };
	button[3] = { BUTTON_LX,BUTTON_RX,END_BUTTON_LY,END_BUTTON_RY,false,eSceneType::eEnd };

	ResourceManager* rm = ResourceManager::GetInstance();
}

// �X�V����
eSceneType TitleScene::Update()
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
	if (can_click && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		PlayButtonSound();

		for (int i = 0; i < BUTTON_NUM; i++)
		{
			if (button[i].collision)
			{
				// ���ꂼ��̉�ʂɑJ��
				return button[i].targetScene;
			}
		}
	}

	return GetNowSceneType();
}

// �`�揈��
void TitleScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(90);
	DrawString(540, 80, "TITLE", 0xffffff);

	int button_color = 0xD6A15D;         // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff;  // �{�^���̕����̃J���[�R�[�h
	int button_string_yspacing = 20;     // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	// �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)
	int start_button_xspacing = 115;
	int help_button_xspacing = 70; 
	int ranking_button_xspacing = 100;
	int end_button_xspacing = 125;

	// ���j���[�{�^��
	DrawButton(BUTTON_NUM, button, button_color);

	// �{�^�������`��(�摜���o���������)
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else if(i == 1)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, "HOW TO PLAY", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else if (i == 2)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + ranking_button_xspacing, button[i].ly + button_string_yspacing, "RANKING", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, "EXIT", button_string_color);
				SetDrawBright(255, 255, 255);
			}

		}
		else
		{
			if (i == 0)
			{
				SetFontSize(30);
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
			}
			else if(i == 1)
			{
				SetFontSize(30);
				DrawString(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, "HOW TO PLAY", button_string_color);
			}
			else if (i == 2)
			{
				SetFontSize(30);
				DrawString(button[i].lx + ranking_button_xspacing, button[i].ly + button_string_yspacing, "RANKING", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, "EXIT", button_string_color);
			}
		}
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