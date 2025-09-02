#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

// �R���X�g���N�^
HelpScene::HelpScene()
{
	frame_count = 0;
	can_click = false;

	// ���X�^�[�g�{�^��������
	button[0] = { START_BUTTON_LX,START_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eGameMain };

	// �^�C�g���{�^��������
	button[1] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eTitle };
}

// �f�X�g���N�^
HelpScene::~HelpScene()
{
}

// ����������
void HelpScene::Initialize()
{
	
}

// �X�V����
eSceneType HelpScene::Update()
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

// �`�揈��
void HelpScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(80);
	DrawString(450, 35, "HOW TO PLAY", 0xffffff);

	int button_color = 0xD6A15D;        // �{�^���̃J���[�R�[�h
	int button_string_color = 0xffffff; // �{�^���̕����̃J���[�R�[�h
	int button_string_yspacing = 20;    // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)

	int start_button_xspacing = 115;   // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)
	int title_button_xspacing = 50;     // �{�^���̕����̕\������ʒu(�{�^������X���W����̋���)

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
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
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
void HelpScene::Finalize()
{
}

// ���݂̃V�[������Ԃ�
eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
