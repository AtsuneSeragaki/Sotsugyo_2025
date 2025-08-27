#include "SceneBase.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"

SceneBase::SceneBase() : background_image(NULL)
{

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
	//DrawGraph(0, 0, background_image, TRUE);
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