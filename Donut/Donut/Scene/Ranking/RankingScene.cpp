#include "RankingScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "DxLib.h"
#include "../../Utility/InputManager.h"

// �R���X�g���N�^
RankingScene::RankingScene()
{
	// �^�C�g���{�^��������
	button[0] = { RANKING_TITLE_BUTTON_LX,RANKING_TITLE_BUTTON_RX,RANKING_BUTTON_LY,RANKING_BUTTON_RY,false,eSceneType::eTitle };
}

// �f�X�g���N�^
RankingScene::~RankingScene()
{
}

// ����������
void RankingScene::Initialize()
{
}

// �X�V����
eSceneType RankingScene::Update()
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
	for (int i = 0; i < RANKING_BUTTON_NUM; i++)
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

		for (int i = 0; i < RANKING_BUTTON_NUM; i++)
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
void RankingScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(90);
	DrawString(500, 35, "RANKING", 0xffffff);

	RankingData* ranking = new RankingData();
	ranking->Initialize();

	SetFontSize(65);
	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		DrawFormatString(425, 155 + i * 90, 0x000000, "No.%d:%08d", i + 1, ranking->GetScore(i));
	}

	int button_color = 0xD6A15D;         // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff;  // �{�^���̕����̃J���[�R�[�h
	int button_string_yspacing = 20;     // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	int title_button_xspacing = 50;

	// ���j���[�{�^��
	DrawButton(RANKING_BUTTON_NUM, button, button_color);

	// �{�^�������`��(�摜���o���������)
	for (int i = 0; i < RANKING_BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if(i == 0)
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
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
			}
		}
	}
}

// �I��������
void RankingScene::Finalize()
{
}

// ���݂̃V�[������Ԃ�
eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}
