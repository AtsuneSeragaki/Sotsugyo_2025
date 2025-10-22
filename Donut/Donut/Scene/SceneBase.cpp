#include "SceneBase.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

SceneBase::SceneBase() : background_image(0),frame_count(0),can_click(false),button_se_handle(0)
{
	ResourceManager* rm = ResourceManager::GetInstance();
	button_se_handle = rm->GetSounds("Resource/Sounds/button_se.mp3");
}

SceneBase::~SceneBase()
{
	this->Finalize();
}

void SceneBase::Initialize()
{

}

eSceneType SceneBase::Update()
{
	return GetNowSceneType();
}

void SceneBase::Draw() const
{
}

void SceneBase::Finalize()
{
	
}

// �v���C���[�J�[�\���ƃ{�^���̓����蔻��(�����F�����蔻�����肽���{�^���̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
int SceneBase::CheckPlayerButtonCollision(int left, int right, int top, int bottom)
{
	InputManager* input = InputManager::GetInstance();

	int player_width = 5;  // �v���C���[�̕�
	int player_hight = 10; // �v���C���[�̍���

	// �v���C���[���
	int player_left = (int)input->GetMouseLocation().x;
	int player_right = (int)input->GetMouseLocation().x + player_width;
	int player_top = (int)input->GetMouseLocation().y;
	int player_bottom = (int)input->GetMouseLocation().y + player_hight;

	// �����蔻��(�l�p���m)
	if ((player_right > left) && (player_left < right))
	{
		if ((player_bottom > top) && (player_top < bottom))
		{
			return 1;
		}
	}

	return 0;
}

// �{�^���`�揈��(�����F�{�^���̐�)
void SceneBase::DrawButton(int button_num, const ButtonState* button,int button_color, int button_line_color) const
{
	for (int i = 0; i < button_num; i++)
	{
		// �{�^���g�̑���
		int button_line_width = 3;

		if (button[i].collision)
		{
			// �v���C���[�J�[�\�����������Ă��鎞�́A�{�^���̐F���Â�����
			SetDrawBright(128, 128, 128);

			// �{�^���w�i�`��
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);

			// �{�^���g�`��(�g�𑾂����邽�߂ɕ����`��)
			for (int j = 0; j < button_line_width; j++)
			{
				DrawBox(button[i].lx - j, button[i].ly - j, button[i].rx + j, button[i].ry + j, button_line_color, FALSE);
			}

			// �`��P�x�����ɖ߂�
			SetDrawBright(255, 255, 255);
		}
		else
		{
			// �{�^���w�i�`��
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);

			// �{�^���g�`��(�g�𑾂����邽�߂ɕ����`��)
			for (int j = 0; j < button_line_width; j++)
			{
				DrawBox(button[i].lx - j, button[i].ly - j, button[i].rx + j, button[i].ry + j, button_line_color, FALSE);
			}
		}
	}
}

// �{�^���̌��ʉ���炷����
void SceneBase::PlayButtonSound()
{
	PlaySoundMem(button_se_handle, DX_PLAYTYPE_BACK, TRUE);
}
