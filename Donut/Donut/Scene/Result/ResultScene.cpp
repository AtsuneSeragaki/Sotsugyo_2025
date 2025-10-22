#include "ResultScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

// �R���X�g���N�^
ResultScene::ResultScene(int score)
{
	this->score = score;
	frame_count = 0;
	can_click = false;

	// ���X�^�[�g�{�^��������
	button[0] = { RESULT_RESTART_BUTTON_LX,RESULT_RESTART_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eGameMain };

	// �^�C�g���{�^��������
	button[1] = { RESULT_TITLE_BUTTON_LX,RESULT_TITLE_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eTitle };
}

// �f�X�g���N�^
ResultScene::~ResultScene()
{
}

// ����������
void ResultScene::Initialize()
{
}

// �X�V����
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
	for (int i = 0; i < RESULT_BUTTON_NUM; i++)
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

		for (int i = 0; i < RESULT_BUTTON_NUM; i++)
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

// �`�揈��
void ResultScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(90);
	DrawString(510, 35, "RESULT", 0xffffff);

	DrawBox(340, 150, 940, 560, 0xffffff, TRUE);

	// �X�R�A
	DrawScore();

	// �����L���O�\��
	DrawRanking();

	int button_color = 0xD6A15D;        // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff; // �{�^���̕����̃J���[�R�[�h
	int button_string_yspacing = 20;    // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	int restart_button_xspacing = 75;   // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)
	int title_button_xspacing = 50;     // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)

	// ���j���[�{�^��
	DrawButton(RESULT_BUTTON_NUM, button, button_color,button_color);

	// �{�^�������`��(�摜���o���������)
	for (int i = 0; i < RESULT_BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "PLAY AGAIN", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			
		}
		else
		{
			if (i == 0)
			{
				SetFontSize(30);
				DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "PLAY AGAIN", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
			}
		}
	}
}

// �I��������
void ResultScene::Finalize()
{
}

// ���݂̃V�[������Ԃ�
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

// �X�R�A�`�揈��
void ResultScene::DrawScore() const
{
	SetFontSize(40);
	DrawFormatString(540, 170, 0x000000, "Your score");
	SetFontSize(70);
	DrawFormatString(502, 230, 0x000000, "%08d", score);
}

// �����L���O�`�揈��
void ResultScene::DrawRanking() const
{
	RankingData* ranking = new RankingData();
	ranking->Initialize();

	SetFontSize(40);
	DrawFormatString(580, 320, 0x000000, "Ranking");
	SetFontSize(40);
	for (int i = 0; i < RANKING_DATA_MAX - 2; i++)
	{
		DrawFormatString(515, 380 + i * 60, 0x000000, "No.%d:%08d",i + 1,ranking->GetScore(i));
	}
}
